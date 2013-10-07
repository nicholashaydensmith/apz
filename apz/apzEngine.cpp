#include "stdafx.h"
#include "apzEngine.h"
#include "apzUtilities.h"

using namespace apz;

static GLFWwindow * mWindow   = NULL;
static Renderer   * mRenderer = NULL;

static void Engine::ErrorCallback(int error, const char* description)
{
  CRITICAL_ERROR(description);
}
static void Engine::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Engine::Init() {

  glfwSetErrorCallback(ErrorCallback);

  if(!glfwInit())
    CRITICAL_ERROR("glfw init failed!");

  mWindow = glfwCreateWindow(640, 480, "Simple Window", NULL, NULL);
  if(!mWindow){
    glfwTerminate();
    CRITICAL_ERROR("window creation failed!");
  }

  glfwMakeContextCurrent(mWindow);

  glewExperimental = true;
  if(glewInit() != GLEW_OK)
    CRITICAL_ERROR("glew init failed!");

  
  glfwSetKeyCallback(mWindow, KeyCallback);


}

void Engine::SetRenderer(Renderer *tRenderer) {
  mRenderer = tRenderer;
}

void Engine::EventLoop() {
  int width = 0, height = 0;
  int width_old = 0, height_old = 0;
  int x = 0, y = 0;
  int x_old = 0, y_old = 0;


  while(!glfwWindowShouldClose(mWindow)){
    width_old = width;  height_old = height;
    x_old = x; y_old = y;

    glfwGetFramebufferSize(mWindow, &width, &height);
    glfwGetWindowPos(mWindow, &x, &y);

    if(width_old != width || height_old != height || x_old != x || y_old != y){
      mRenderer->Resize(width, height, 0, 0);
    }

    mRenderer->Render();

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }

  glfwDestroyWindow(mWindow);
  glfwTerminate();
}
