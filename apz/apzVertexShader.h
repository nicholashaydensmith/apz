#pragma once
#include "stdafx.h"
#include "apzShaderObject.h"
#include "apzData.h"

namespace apz {
  class VertexShader : public ShaderObject{

  public:
    VertexShader(Data &tData);

    ~VertexShader();

  protected:
    void Load(Data &tData);

  };
};