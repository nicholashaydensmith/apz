#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include "apzUtilities.h"
#include "apzRenderObject.h"
#include "stdafx.h"
#include "apzShader.h"
#include "apzData.h"

namespace apz {
class WFObject : public RenderObject {
public:
	WFObject(const char *filename);
	~WFObject();
	virtual void Render(MATRIX_RENDER_INFO_T &, Shader &);
private:
	int lineNr;
	typedef void (WFObject::*function)(const std::string &);
	GLuint m_vbo;
	GLuint m_ebo;
	unsigned long m_dataSize;
	uint16_t attributes;
	enum OBJATTRIBUTES {
		VERT     = 0,  // v  - Geometric vertices
		TEXVERT  = 1,  // vt - Texture Vertices
		NORMVERT = 2,  // vn - Vertex Normals
		PARVERT  = 3,  // vp - Parameter space Vertices
		POINT    = 4,  // p  - Point
		LINE     = 5,  // l  - Line
		FACE     = 6,  // f  - Face
		GROUP    = 7,  // g  - Group
		SGROUP   = 8,  // s  - Smoothing group
		OBJNM    = 9,  // o  - Object name
		MTL      = 10, // Has materials
	};
	typedef struct {
		float x, y, z, nx, ny, nz;
	} WFVertex;
	typedef struct {
		unsigned int v1, v2, v3;
	} WFFace;
	typedef struct {
		float Ka[3];  // Ambient Color
		float Kd[3];  // Diffuse Color
		float Ks[3];  // Specular Color
		float Ns;     // Specular (coeff)
	} WFMaterial;
	typedef struct {
		WFVertex     fn;
		WFMaterial   *mtl;
	} WFFaceInfo;
	typedef struct {
		int              index;
		std::vector<int> fns;   
	} WFVertexInfo;
	std::vector<WFVertex> vertices;
	std::vector<WFFace> faces;
	std::vector<WFMaterial> materials;
	std::vector<WFFaceInfo> faceInfo;
	std::vector<WFVertexInfo> vertexInfo;
	std::map<std::string,WFMaterial *> mtlFile;
	WFMaterial *currMaterial;
	std::map<std::string, function> funcMap;
	void parseFile(const char *filename, std::string type);
	void parseLine(const std::string &line);
	void parseVertex(const std::string &line);
	void parseNormal(const std::string &line);
	void parseVertexTexture(const std::string &line);
	void parseFace(const std::string &line);
	void loadMaterials(const std::string &line);
	void parseMaterial(const std::string &line);
	void useMaterial(const std::string &line);
	void parseAmbientColor(const std::string &line);
	void parseDiffuseColor(const std::string &line);
	void parseSpecularColor(const std::string &line);
	void parseSpecularCoeff(const std::string &line);
	bool testAttribute(const uint16_t t);
	void addAttribute(const uint16_t t);
	WFVertex cross(WFVertex v1, WFVertex v2, WFVertex v3);
	void calculateNormals();
};
}