#pragma once
#include "stdafx.h"
#include "apzStructs.h"
#include "apzRenderObject.h"
#include <list>

namespace apz {

  class RenderGroup : public RenderObject {
  public:
    virtual void Render(MATRIX_RENDER_INFO_T &tMatInfo, Shader &tShader);

    virtual void Add(RenderObject *tObj);
    unsigned long GetSize();

  protected:
    std::vector<RenderObject *> m_objList;
  };
};