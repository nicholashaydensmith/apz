#pragma once
#include "stdafx.h"
#include "apzStructs.h"
#include "apzShader.h"

namespace apz {
  class RenderObject {

  public:  
    virtual void Render(MATRIX_RENDER_INFO_T &, Shader &);
  };
};