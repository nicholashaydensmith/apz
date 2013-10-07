#pragma once
#include "stdafx.h"
#include "apzStructs.h"
#include "apzSwitchRenderGroup.h"
#include <list>

namespace apz {

  class SwitchRGOpacity : public SwitchRenderGroup {
  public:
    SwitchRGOpacity();

    virtual void Render(MATRIX_RENDER_INFO_T &tMatInfo, Shader &tShader);

    void SetFadeAmount(float tAlpha);

  protected:
    float m_fadeAmount;
  };
};