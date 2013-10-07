#include "stdafx.h"
#include "apzSwitchRGOpacity.h"
#include "apzUtilities.h"

using namespace apz;


SwitchRGOpacity::SwitchRGOpacity() : SwitchRenderGroup(), m_fadeAmount(0.005) {

}

void SwitchRGOpacity::Render(MATRIX_RENDER_INFO_T &tMatInfo, Shader &tShader) {
  int secI = m_currentIndex;
  float cur_opacity = 1.0;

  tShader.SetUniform(tShader.GetUniform("opacity"), cur_opacity);
  m_objList[secI]->Render(tMatInfo, tShader);
  secI--;
  if(secI < 0){
    secI = m_objList.size() - 1;
  }
  cur_opacity -= m_fadeAmount;


  while(secI != m_currentIndex && cur_opacity > 0.0){

    tShader.SetUniform(tShader.GetUniform("opacity"), cur_opacity);
    m_objList[secI]->Render(tMatInfo, tShader);

    secI--;
    if(secI < 0){
      secI = m_objList.size() - 1;
    }
    cur_opacity -= m_fadeAmount;
  }
}

void SwitchRGOpacity::SetFadeAmount(float tAlpha) {
  m_fadeAmount = tAlpha;
}