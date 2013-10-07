#pragma once
#include "stdafx.h"
#include "apzShaderObject.h"
#include "apzData.h"

namespace apz {
  class GeometryShader : public ShaderObject{

  public:
    GeometryShader(Data &tData);
    ~GeometryShader();

  protected:
    void Load(Data &tData);
  };
};