#include "stdafx.h"
#include "apzGeometryShader.h"
#include "apzUtilities.h"

using namespace apz;
GeometryShader::GeometryShader(Data &tData) {
  // Load shader itself from this data
  Load(tData);

}

GeometryShader::~GeometryShader() {

}

void GeometryShader::Load(Data &tData) {

  char *buffer;
  unsigned long len;


  tData.copyAndAllocate(&buffer, &len);
  int cake = (int)len;


  m_shaderId = glCreateShader(GL_GEOMETRY_SHADER);

  CHECK_GL_ERROR();

  glShaderSourceARB(m_shaderId, 1, (const GLcharARB **)&buffer, (GLint *)&cake);
  CHECK_GL_ERROR();

  glCompileShaderARB(m_shaderId);
  CHECK_GL_ERROR();

  GLint compiled;
  glGetObjectParameterivARB(m_shaderId, GL_COMPILE_STATUS, &compiled);
  if(!compiled)
    util::GetGLCompileLog(m_shaderId);

  free(buffer);
}


