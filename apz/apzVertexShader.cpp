#include "stdafx.h"
#include "apzVertexShader.h"
#include "apzUtilities.h"

using namespace apz;

VertexShader::VertexShader(Data &tData) {
  Load(tData);
}

VertexShader::~VertexShader() {

}

void VertexShader::Load(Data &tData) {
  char *buffer;
  unsigned long len;

  tData.copyAndAllocate(&buffer, &len);


  m_shaderId = glCreateShader(GL_VERTEX_SHADER);
  CHECK_GL_ERROR();

  glShaderSourceARB(m_shaderId, 1, (const GLcharARB **)&buffer, (GLint *)&len);
  CHECK_GL_ERROR();

  glCompileShaderARB(m_shaderId);
  CHECK_GL_ERROR();

  GLint compiled;
  glGetObjectParameterivARB(m_shaderId, GL_COMPILE_STATUS, &compiled);
  if(!compiled)
    util::GetGLCompileLog(m_shaderId);

  free(buffer);
}


