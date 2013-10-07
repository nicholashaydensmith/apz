#pragma once
#include "stdafx.h"
#include "apzStructs.h"

namespace apz {

  class Renderer {
  public:
    Renderer(WINDOW_DATA *tWinData);
    virtual void Render();
    virtual void Resize(GLuint width, GLuint height, GLuint x, GLuint y);
    virtual void Setup(GLuint x, GLuint y, GLuint width, GLuint height);
    virtual void Kill();

  protected:
    MATRIX_RENDER_INFO_T m_matrix;
    WINDOW_DATA *m_window;
  };

};