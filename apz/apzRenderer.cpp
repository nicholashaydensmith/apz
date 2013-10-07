#include "stdafx.h"
#include "apzRenderer.h"
#include "apzUtilities.h"

using namespace apz;

void Renderer::Setup(GLuint x, GLuint y, GLuint width, GLuint height) {
  CRITICAL_ERROR("undefined render setup function called");
}

void Renderer::Render() {
  CRITICAL_ERROR("undefined render function called");
}

void Renderer::Resize(GLuint width, GLuint height, GLuint x, GLuint y) {
  CRITICAL_ERROR("undefined render resize function called");
}

Renderer::Renderer(WINDOW_DATA *tWin) : m_window(tWin){
}

void Renderer::Kill() {

}