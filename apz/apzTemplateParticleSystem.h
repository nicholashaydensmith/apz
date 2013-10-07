#pragma once
#include "stdafx.h"
#include "apzRenderObject.h"
#include "apzShader.h"
#include "apzData.h"
#include "apzUtilities.h"

namespace apz {

  
  class TemplateParticleSystem : public RenderObject {
  public:
	  TemplateParticleSystem(Data &tData, int x, ...);
	  virtual void Render(MATRIX_RENDER_INFO_T &, Shader &);

	  enum GLSLDataTypes {
		  FLOAT, DOUBLE, BOOL, INT, UINT,
		  VEC2, VEC3, VEC4,
		  DVEC2, DVEC3, DVEC4,
		  BVEC2, BVEC3, BVEC4,
		  IVEC2, IVEC3, IVEC4,
		  UVEC2, UVEC3, UVEC4,
		  MAT2, DMAT2,
		  MAT3, DMAT3,
		  MAT4, DMAT4,
		  MAT2x3, MAT2x4,
		  MAT3x2, MAT3x4,
		  MAT4x2,
	  };

	  typedef struct {
		  unsigned long offset;
		  unsigned long size;
		  GLSLDataTypes type;
		  std::string name;
		  GLint shaderloc;
		  int normalize;
	  }ATTRIB_DATA;

	  void EvaluateShaderLocations(Shader &tShader);

  private:
	   std::vector<ATTRIB_DATA *>m_attribs;
	   unsigned long m_dataSizePerElement;

	   char *m_data;
	   unsigned long m_dataFullSize;
	   unsigned long m_dataElementCount;

	   GLuint m_vbo;

	  unsigned long GetSizeOfType(GLSLDataTypes tType);
	  int GetRenderElementCount(GLSLDataTypes type);
	  int GetRenderElementType (GLSLDataTypes type);

  };
};