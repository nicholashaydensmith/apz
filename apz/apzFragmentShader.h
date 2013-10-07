#pragma once
#include "stdafx.h"
#include "apzShaderObject.h"
#include "apzData.h"

namespace apz {
  class FragmentShader : public ShaderObject{

  public:
    FragmentShader(Data &tData);
    ~FragmentShader();

  protected:
    void Load(Data &tData);
  };
};