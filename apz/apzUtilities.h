#pragma once

#include "stdafx.h"

//#define CHECK_GL_ERROR_SILENT
#define CHECK_GL_ERROR() apz::util::CheckGLError(__FILE__, __LINE__)
#define CRITICAL_ERROR(a) apz::util::CriticalError(a, __FILE__, __LINE__)

namespace apz {
  namespace util {

    int CheckGLError(char *file, int line);
    int CriticalError(const char *tErrorText, char *tFile, int tLine);
    int FileToMemory(const char *tFilepath, char **tsDest, unsigned long *tSize);
    void GetGLCompileLog(GLuint tShaderId);
    void GetGLLinkerLog(GLuint tProgramId);
  };
};