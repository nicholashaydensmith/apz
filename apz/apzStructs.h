#pragma once
#include "stdafx.h"

// This struct defines everything that will be passed through Render()
// calls.
typedef struct {
  glm::mat4 pj;
  glm::mat4 mv;
  float t;
}MATRIX_RENDER_INFO_T;

typedef struct{
  HGLRC     m_hRC;
  HDC       m_hDC;
  HWND      m_hWnd;
  HINSTANCE m_hInstance;
}WINDOW_DATA;