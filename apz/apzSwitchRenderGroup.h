#pragma once
#include "stdafx.h"
#include "apzStructs.h"
#include "apzRenderGroup.h"
#include <list>

namespace apz {

  class SwitchRenderGroup : public RenderGroup {
  public:

    virtual void Render(MATRIX_RENDER_INFO_T &tMatInfo, Shader &tShader);
    virtual void Add(RenderObject *tObj);
    virtual void Switch(int tIndex);
    virtual void Inc();

  protected:
    RenderObject *m_currentObject;
    int m_currentIndex;
  };
};