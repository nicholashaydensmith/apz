#include "stdafx.h"
#include "apzWaveFrontLoader.h"
#include <fstream>
#include <stdio.h>

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

using namespace apz;

WFObject::WFObject(const char *filename):
	lineNr(0), 
	attributes(0)
{
	funcMap["v"]      = &WFObject::parseVertex;
	funcMap["vt"]     = &WFObject::parseVertexTexture;
	funcMap["vn"]     = &WFObject::parseNormal;
	funcMap["f"]      = &WFObject::parseFace;
	funcMap["mtllib"] = &WFObject::loadMaterials;
	funcMap["usemtl"] = &WFObject::useMaterial;
	funcMap["newmtl"] = &WFObject::parseMaterial;
	funcMap["Ka"]     = &WFObject::parseAmbientColor;
	funcMap["Kd"]     = &WFObject::parseDiffuseColor;
	funcMap["Ks"]     = &WFObject::parseSpecularColor;
	funcMap["Ns"]     = &WFObject::parseSpecularCoeff;

	parseFile(filename, ".obj");
	calculateNormals();
	
	m_dataSize = sizeof(float)*3*faces.size();
	glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(WFVertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(WFFace)*faces.size(), faces.data(), GL_STATIC_DRAW);
	std::cout << "Number of Faces: " << faces.size() << std::endl <<
		"Number of vertices: " << vertices.size() << std::endl;
}

WFObject::~WFObject(){
	std::vector<WFFace>::iterator itor = faces.begin();
//	for(;itor != faces.end(); ++itor) delete itor->mtl;
	std::map<std::string, WFMaterial *>::iterator itor2 = mtlFile.begin();
	for(;itor2 != mtlFile.end(); ++itor2) delete itor2->second;
	delete currMaterial;
}

void WFObject::parseFile(const char *filename, std::string type){
	lineNr = 0;
	std::ifstream inputFile;
	inputFile.open(filename);
	if(inputFile.is_open()){
		std::string line;
		while(inputFile.good()){
			++lineNr;
			std::getline(inputFile,line);
			parseLine(line);
		}
	}else {
		std::string error = "Cannot open " + type + "file: File not found!";
		CRITICAL_ERROR(error.c_str());
	}
	inputFile.close();
}

/* More error handling should exist!
*/
void WFObject::parseLine(const std::string &line){
	if(line.length() < 1) return;
	std::string cmd = line.substr(0,line.find_first_of(" "));
	if(cmd.empty()) return;
	if(cmd[0] == '#') return;
	try {
		function fn = funcMap[cmd];
		if(fn == NULL) {
			//std::cout << "Line " + std::to_string(lineNr) + ": " + cmd + ": Unknown command" << std::endl;
			return;
			//throw std::runtime_error::exception((std::to_string(lineNr) + type + ": Unknown command").c_str());
		}
	   (this->*funcMap[cmd])(line);
	}catch(std::runtime_error &e){
		CRITICAL_ERROR(e.what());
	}
}

void WFObject::parseVertex(const std::string &line){
	addAttribute(VERT);
	vertices.push_back(WFVertex());
	vertexInfo.push_back(WFVertexInfo());
	sscanf_s(line.c_str(), "v %f %f %f", &vertices.back().x, &vertices.back().y, &vertices.back().z);
	vertices.back().x /= 10;
	vertices.back().y /= 10;
	vertices.back().z /= 10;
	vertices.back().nx = vertices.back().ny = vertices.back().nz = 0;
	vertexInfo.back().index = vertexInfo.size() - 1;
}

void WFObject::parseNormal(const std::string &line){
	addAttribute(NORMVERT);
	sscanf_s(line.c_str(), "vn %f %f %f", &vertices.back().nx, &vertices.back().ny, &vertices.back().nz);
}

void WFObject::parseFace(const std::string &line){
	addAttribute(FACE);
	int fill = 0;
	bool norms = true;
	faceInfo.push_back(WFFaceInfo());
	faces.push_back(WFFace());
	unsigned int v1,v2,v3,vn1,vn2,vn3;
	if(sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d", &v1,
                                                        &vn1,
                                                        &v2,
                                                        &vn2,
                                                        &v3,
                                                        &vn3) <= 1)
    {
		if(sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1,
                                                     &fill,
                                                     &vn1,
                                                     &v2,
                                                     &fill,
                                                     &vn2,
                                                     &v3,
                                                     &fill,
                                                     &vn3) <= 1){
				norms = false;
	            sscanf_s(line.c_str(), "f %d %d %d", &v1,
                                                     &v2,
                                                     &v3);
														 
		}
    }
	faces.back().v1 = v1;
	faces.back().v2 = v2;
	faces.back().v3 = v3;
	faceInfo.back().fn = cross(vertices[v1-1], vertices[v2-1], vertices[v3-1]);
	int i = faceInfo.size() - 1;
	vertexInfo[v1-1].fns.push_back(i);
	vertexInfo[v2-1].fns.push_back(i);
	vertexInfo[v3-1].fns.push_back(i);
	if(testAttribute(MTL) && currMaterial != NULL) faceInfo.back().mtl = currMaterial;
}

void WFObject::parseVertexTexture(const std::string &line){
	if(testAttribute(TEXVERT)) return;
	addAttribute(TEXVERT);
	std::cout << "Command \"vt\" not supported" << std::endl;
}

void WFObject::loadMaterials(const std::string &line){
	std::string filename = line.substr(line.find_first_of(" ")+1,line.length()-1);
	parseFile(filename.c_str(), ".mtl");
}

void WFObject::parseMaterial(const std::string &line){
	std::string mtlName = line.substr(line.find_first_of(" ")+1,line.length()-1);
	materials.push_back(WFMaterial());
	mtlFile[mtlName] = &materials.back();
	addAttribute(MTL);
}

void WFObject::useMaterial(const std::string &line){
	std::string mtlName = line.substr(line.find_first_of(" ")+1,line.length()-1);
	if(mtlFile[mtlName] == NULL){
			std::cout << mtlName + ": texture not found" << std::endl;
			return;
	} else currMaterial = mtlFile[mtlName];
}

void WFObject::parseAmbientColor(const std::string &line){
	sscanf_s(line.c_str(), "Ka %f %f %f", &materials.back().Ka[0], 
		                                  &materials.back().Ka[1], 
										  &materials.back().Ka[2]);
}

void WFObject::parseDiffuseColor(const std::string &line){
	sscanf_s(line.c_str(), "Kd %f %f %f", &materials.back().Kd[0], 
		                                  &materials.back().Kd[1], 
										  &materials.back().Kd[2]);
}

void WFObject::parseSpecularColor(const std::string &line){
	sscanf_s(line.c_str(), "Ks %f %f %f", &materials.back().Ks[0], 
		                                  &materials.back().Ks[1], 
										  &materials.back().Ks[2]);
}

void WFObject::parseSpecularCoeff(const std::string &line){
	sscanf_s(line.c_str(), "Ns %f", &materials.back().Ns);
}


bool WFObject::testAttribute(const uint16_t t){
	return (attributes & (1 << t));
}

void WFObject::addAttribute(const uint16_t t){
	if(testAttribute(t)) return;
	else{
		attributes += (1 << t);
	}
}

void WFObject::Render(MATRIX_RENDER_INFO_T &tMatrixInfo, Shader &tShaderInfo){
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glEnableVertexAttribArray(tShaderInfo.GetLAVertex());
  glVertexAttribPointer    (tShaderInfo.GetLAVertex(), 3, GL_FLOAT, GL_FALSE, sizeof(WFVertex), NULL);
  glEnableVertexAttribArray(tShaderInfo.GetLANormal());
  glVertexAttribPointer    (tShaderInfo.GetLANormal(), 3, GL_FLOAT, GL_FALSE, sizeof(WFFace), BUFFER_OFFSET(sizeof(float)*3));
  //glDrawArrays(GL_POINTS, 0, m_dataSize);
  glDrawElements( GL_TRIANGLES, 3*faces.size(), GL_UNSIGNED_INT, 0 );
}

WFObject::WFVertex WFObject::cross(WFVertex v1, WFVertex v2, WFVertex v3){
	WFVertex result;
	WFVertex u, v;
	u.x = v1.x - v2.x;
	u.y = v1.y - v2.y;
	u.z = v1.z - v2.z;
	v.x = v3.x - v2.x;
	v.y = v3.y - v2.y;
	v.z = v3.z - v2.z;
	result.x = result.y = result.z = 0;
	result.nx = u.y * v.z - u.z * v.y;
	result.ny = u.z * v.x - u.x * v.z;
	result.nz = u.x * v.y - u.y * v.x;
	return result;
}

void WFObject::calculateNormals(){
	std::vector<WFVertexInfo>::iterator itor = vertexInfo.begin();
	int i = 0;
	for(;itor != vertexInfo.end(); ++itor, ++i){
		float nx = 0.0, ny = 0.0, nz = 0.0, n = 0.0;
		std::vector<int>::iterator norm = itor->fns.begin();
		for(;norm != itor->fns.end(); ++norm, ++n){
			nx += faceInfo[*norm].fn.nx;
			ny += faceInfo[*norm].fn.ny;
			nz += faceInfo[*norm].fn.nz;
		}
		if(n == 0.0) continue;
		vertices[itor->index].nx = nx/n;
		vertices[itor->index].ny = ny/n;
		vertices[itor->index].nz = nz/n;
	}
}