#include "stdafx.h"
#include "apzTemplateParticleSystem.h"

using namespace apz;

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

TemplateParticleSystem::TemplateParticleSystem(Data &tData, int tCount, ...) {

	/*  Evaluate arguments  */
	std::vector<int> argumentList;
	va_list arguments;
	va_start(arguments, tCount);

	GLSLDataTypes cArg;
	std::string cArgString;
	char *cArgStringTmp;
	ATTRIB_DATA *tmpData;
	unsigned long currentOffset = 0;

	for(int i = 0; i < tCount; i += 2){
		cArgStringTmp = va_arg(arguments, char *);
		cArg = va_arg(arguments, GLSLDataTypes);



		tmpData = new ATTRIB_DATA;

		if(cArgStringTmp[0] == '~'){
			cArgString = std::string(cArgStringTmp + 1);
			tmpData->normalize = GL_TRUE;
		}else{
			cArgString = std::string(cArgStringTmp);
			tmpData->normalize = GL_FALSE;
		}

		tmpData->type = cArg;
		tmpData->offset = currentOffset;
		tmpData->size = GetSizeOfType(cArg);
		tmpData->name = cArgString;

		currentOffset += tmpData->size;

		m_attribs.push_back(tmpData);
	}
	va_end(arguments);

	m_dataSizePerElement = currentOffset;

	/*  DONE EVALUATING TYPE  */

	/*  Read the data based on the evaluated type  */

	tData.copyAndAllocate(&m_data, &m_dataFullSize);
	m_dataElementCount = m_dataFullSize / m_dataSizePerElement;


	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_dataSizePerElement * m_dataElementCount, m_data, GL_STATIC_DRAW);
}

void TemplateParticleSystem::EvaluateShaderLocations(Shader &tShader) {
	for(int i = 0; i < m_attribs.size(); i++){
		m_attribs[i]->shaderloc = glGetAttribLocation(tShader.GetProgramObject(), (m_attribs[i]->name).c_str());
	}
}

int TemplateParticleSystem::GetRenderElementCount(GLSLDataTypes tType) {
	switch(tType) {
	case   FLOAT  : return 1;
	case   DOUBLE : return 1;
	case   BOOL   : return 1;
	case   INT    : return 1;
	case   UINT   : return 1;
	case   VEC2   : return 2;
	case   VEC3   : return 3;
	case   VEC4   : return 4;
	case   DVEC2  : return 2;
	case   DVEC3  : return 3;
	case   DVEC4  : return 4;
	case   BVEC2  : return 2;
	case   BVEC3  : return 3;
	case   BVEC4  : return 4;
	case   IVEC2  : return 2;
	case   IVEC3  : return 3;
	case   IVEC4  : return 4;
	case   UVEC2  : return 2;
	case   UVEC3  : return 3;
	case   UVEC4  : return 4;
	case   MAT2   : return 4;
	case   DMAT2  : return 4;
	case   MAT3   : return 9;
	case   DMAT3  : return 9;
	case   MAT4   : return 16;
	case   DMAT4  : return 16;
	case   MAT2x3 : return 6;
	case   MAT2x4 : return 8;
	case   MAT3x2 : return 6;
	case   MAT3x4 : return 12;
	case   MAT4x2 : return 8;
	}

	return 0;
}

int TemplateParticleSystem::GetRenderElementType (GLSLDataTypes tType) {
	switch(tType) {
	case   FLOAT  : return GL_FLOAT;
	case   DOUBLE : return GL_DOUBLE;
	case   BOOL   : return GL_BOOL;
	case   INT    : return GL_INT;
	case   UINT   : return GL_UNSIGNED_INT;
	case   VEC2   : return GL_FLOAT;
	case   VEC3   : return GL_FLOAT;
	case   VEC4   : return GL_FLOAT;
	case   DVEC2  : return GL_DOUBLE;
	case   DVEC3  : return GL_DOUBLE;
	case   DVEC4  : return GL_DOUBLE;
	case   BVEC2  : return GL_BOOL;
	case   BVEC3  : return GL_BOOL;
	case   BVEC4  : return GL_BOOL;
	case   IVEC2  : return GL_INT;
	case   IVEC3  : return GL_INT;
	case   IVEC4  : return GL_INT;
	case   UVEC2  : return GL_UNSIGNED_INT;
	case   UVEC3  : return GL_UNSIGNED_INT;
	case   UVEC4  : return GL_UNSIGNED_INT;
	case   MAT2   : return GL_FLOAT;
	case   DMAT2  : return GL_DOUBLE;
	case   MAT3   : return GL_FLOAT;
	case   DMAT3  : return GL_DOUBLE;
	case   MAT4   : return GL_FLOAT;
	case   DMAT4  : return GL_DOUBLE;
	case   MAT2x3 : return GL_FLOAT;
	case   MAT2x4 : return GL_FLOAT;
	case   MAT3x2 : return GL_FLOAT;
	case   MAT3x4 : return GL_FLOAT;
	case   MAT4x2 : return GL_FLOAT;
	}

	return 0;
}

void TemplateParticleSystem::Render(MATRIX_RENDER_INFO_T &, Shader &) {

	for(int i = 0; i < m_attribs.size(); i++){
		if(m_attribs[i]->shaderloc != -1){
			glEnableVertexAttribArray(m_attribs[i]->shaderloc);
			glVertexAttribPointer    (
				m_attribs[i]->shaderloc, 
				GetRenderElementCount(m_attribs[i]->type), 
				GetRenderElementType(m_attribs[i]->type),
				m_attribs[i]->normalize,
				m_dataSizePerElement,
				BUFFER_OFFSET(m_attribs[i]->offset)
				);
		}
	}

	glDrawArrays(GL_POINTS, 0, m_dataElementCount
		);
}


unsigned long TemplateParticleSystem::GetSizeOfType(GLSLDataTypes tType) {
	switch(tType) {
	case   FLOAT  : return sizeof(GLfloat);
	case   DOUBLE : return sizeof(GLdouble);
	case   BOOL   : return sizeof(GLboolean);
	case   INT    : return sizeof(GLint);
	case   UINT   : return sizeof(GLuint);
	case   VEC2   : return sizeof(GLfloat)*2;
	case   VEC3   : return sizeof(GLfloat)*3;
	case   VEC4   : return sizeof(GLfloat)*4;
	case   DVEC2  : return sizeof(GLdouble)*2;
	case   DVEC3  : return sizeof(GLdouble)*3;
	case   DVEC4  : return sizeof(GLdouble)*4;
	case   BVEC2  : return sizeof(GLboolean)*2;
	case   BVEC3  : return sizeof(GLboolean)*3;
	case   BVEC4  : return sizeof(GLboolean)*4;
	case   IVEC2  : return sizeof(GLint)*2;
	case   IVEC3  : return sizeof(GLint)*3;
	case   IVEC4  : return sizeof(GLint)*4;
	case   UVEC2  : return sizeof(GLuint)*2;
	case   UVEC3  : return sizeof(GLuint)*3;
	case   UVEC4  : return sizeof(GLuint)*4;
	case   MAT2   : return sizeof(GLfloat)*4;
	case   DMAT2  : return sizeof(GLdouble)*4;
	case   MAT3   : return sizeof(GLfloat)*9;
	case   DMAT3  : return sizeof(GLdouble)*9;
	case   MAT4   : return sizeof(GLfloat)*16;
	case   DMAT4  : return sizeof(GLdouble)*16;
	case   MAT2x3 : return sizeof(GLfloat)*6;
	case   MAT2x4 : return sizeof(GLfloat)*8;
	case   MAT3x2 : return sizeof(GLfloat)*6;
	case   MAT3x4 : return sizeof(GLfloat)*12;
	case   MAT4x2 : return sizeof(GLfloat)*8;
	}

	return 0;
}