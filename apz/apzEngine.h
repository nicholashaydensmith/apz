#pragma once

#include "stdafx.h"
#include "apz.h"
#include "apzDefaultRenderer.h"

namespace apz {

  class Engine {
  public:
    Engine();
    ~Engine();

    void SetRenderer(Renderer *tRenderer);


  private:
    Renderer *m_renderer;


  };

};