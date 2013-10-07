#pragma once

#include "stdafx.h"

#include "apzShader.h"

namespace apz {
  class ShaderCollection {
  public:
    ShaderCollection();
    ShaderCollection(ShaderCollection &);
    ~ShaderCollection();


    Shader *CreateShader();
    Shader *GetShader(int i);
    void SwitchShader(int i);

  private:
    std::vector<Shader *> mShaders;


  };

};