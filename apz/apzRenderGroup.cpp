#include "stdafx.h"
#include "apzRenderGroup.h"

using namespace apz;

void RenderGroup::Add(RenderObject *tObj) {
  m_objList.push_back(tObj);
}

unsigned long RenderGroup::GetSize() {
  return m_objList.size();
}

void RenderGroup::Render(MATRIX_RENDER_INFO_T &tMatInfo, Shader &tShader) {
  std::vector<RenderObject *>::iterator it;

  for(it = m_objList.begin(); it != m_objList.end(); ++it)
    (*it)->Render(tMatInfo, tShader);
}