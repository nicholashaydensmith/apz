// apz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "apzWindow.h"
#include "apzZSpaceRenderer.h"
#include "apzParticleSystem.h"


int main(int argc, char *argv[]) {

  int zsy = 0, zsx = 0;
  // Query zSpace Coordinates
  /* Get ZSpace Display Coordinates */
  zspace::common::DisplayInfo displayInfo;
  int index = 0;
  int numDisplays = displayInfo.getNumDisplays();
  while (index < numDisplays && !displayInfo.getDisplay(index)->isZSpaceDisplay)
    index++;

  // If a zSpace display was found, then position the window on the zSpace
  if (index < numDisplays)
  {
    const zspace::common::DisplayInfo::Display* display = displayInfo.getDisplay(index);
    zsx = display->displayPosition[0];
    zsy = display->displayPosition[1];
  }

  // Create a new window for rendering
  apz::Window *f_win = new apz::Window("Hello!", zsx, zsy, 1920, 1080);

  // Create a new Renderer, and attach to the window
  apz::ZSpaceRenderer *f_rend = new apz::ZSpaceRenderer(f_win->getWindowData());
  f_win->SetRenderer(f_rend);

  // Initialize the window (and consequently renderer)
  f_win->Initialize();

  // Begin the event loop for rendering
  f_win->BeginEventLoop();

  // Cleanup
  delete f_win;
  delete f_rend;

  return EXIT_SUCCESS;
}

