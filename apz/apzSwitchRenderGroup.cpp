#include "stdafx.h"
#include "apzSwitchRenderGroup.h"

using namespace apz;

void SwitchRenderGroup::Render(MATRIX_RENDER_INFO_T &tMatInfo, Shader &tShader) {
  // Only render the current iterator
  m_currentObject->Render(tMatInfo, tShader);
}

void SwitchRenderGroup::Add(RenderObject *tObj) {
  RenderGroup::Add(tObj);

  if(GetSize() == 1){
    m_currentObject = tObj;
    m_currentIndex = 0;
  }
}

void SwitchRenderGroup::Switch(int tIndex) {
  if(tIndex >= GetSize()){
    tIndex = 0;
  }

  m_currentIndex = tIndex;
  m_currentObject = m_objList[m_currentIndex];
}

void SwitchRenderGroup::Inc() {
  m_currentIndex++;
  if(m_currentIndex >= GetSize()){
    m_currentIndex = 0;
  }

  m_currentObject = m_objList[m_currentIndex];
}