#include "stdafx.h"
#include "apzUtilities.h"
#include <sstream>

using namespace apz;

int util::CriticalError(const char *tErrorText, char *tFile, int tLine) {
  std::string error_text(tFile);

  error_text += ":";
  error_text += tLine;
  error_text += " // ";
  error_text += tErrorText;

#ifdef WIN32
  MessageBox(NULL, error_text.c_str(), "OpenGL Error", MB_OK);
#else
  std::cout << error_text;
  fgetc(stdin);
#endif
  exit(EXIT_FAILURE);
}

int util::CheckGLError(char *file, int line) {
  GLenum gl_err;
  int ret_code = 0;
  std::stringstream error_text;


  gl_err = glGetError();

  while(gl_err != GL_NO_ERROR){
    const GLubyte *s_error = gluErrorString(gl_err);

    error_text << (char *)s_error << " AT " << file << ":" << line << "\n";

    ret_code = 1;
    gl_err = glGetError();
  }

#ifndef CHECK_GL_ERROR_SILENT
  if(ret_code == 1){
    CriticalError(error_text.str().c_str(), file, line);
  }
#endif

  return ret_code;
}

int util::FileToMemory(const char *tFilepath, char **tsDest, unsigned long *tSize) {
  std::ifstream FP(tFilepath, std::ios_base::in | std::ios_base::binary);

  if(!FP.good()){
    return 0;
  }

  FP.seekg(0, FP.end);
  size_t len = FP.tellg();
  FP.seekg(0, FP.beg);

  *tSize = len;
  *tsDest = (char *)malloc(sizeof(char) * len);


  FP.read(*tsDest, *tSize);

  FP.close();

  return 1;
}

void util::GetGLCompileLog(GLuint tShaderId) {
  GLint blen = 0;
  GLsizei slen = 0;

  glGetShaderiv(tShaderId, GL_INFO_LOG_LENGTH, &blen);

  if(blen > 1){
    GLchar *compiler_log = (GLchar*)malloc(blen);

    glGetInfoLogARB(tShaderId, blen, &slen, compiler_log);

    CRITICAL_ERROR(compiler_log);
    free(compiler_log);
  }

}

void util::GetGLLinkerLog(GLuint tProgramId) {
  GLint blen = 0;
  GLsizei slen = 0;

  glGetProgramiv(tProgramId, GL_INFO_LOG_LENGTH, &blen);

  if(blen > 1){
    GLchar *compiler_log = (GLchar*)malloc(blen);

    glGetInfoLogARB(tProgramId, blen, &slen, compiler_log);

    CRITICAL_ERROR(compiler_log);
    free(compiler_log);
  }

}

