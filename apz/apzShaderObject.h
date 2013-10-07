#pragma once
#include "stdafx.h"

namespace apz {
  class ShaderObject {
  public:
    // Methods that must be overriden by spec
    //virtual void Compile();

    // Default methods
    GLuint GetShaderID();

  protected:
    GLchar *mSource;
    GLuint m_shaderId;
  };
};