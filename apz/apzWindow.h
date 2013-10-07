#pragma once
#include "stdafx.h"
#include "apzShaderObject.h"
#include "apzRenderer.h"
#include <map>

namespace apz {
  class Window {

  public:
    Window(const char *tName, int tX, int tY, int tWidth, int tHeight);
    ~Window();

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    void BeginEventLoop();
    Renderer *GetRenderer();
    void SetRenderer(Renderer *tRenderer);

    HGLRC        getRenderingContext() const;
    HDC          getDeviceContext() const;
    HWND         getWindowHandle() const;
    HINSTANCE    getApplicationInstance() const;
    WINDOW_DATA *getWindowData();

    static LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    void Initialize();

  private:
    void winInit();
    void winKill();

    /* API Internals */
    Renderer *m_renderer;

    /* Windows Components */
    bool m_winActive;
    static int m_id;
    static std::map<HWND, Window *> m_windowMap;

    std::string m_windowName;
    std::string m_windowClassName;

    int m_x;
    int m_y;
    int m_width;
    int m_height;



    WINDOW_DATA m_win;


    LRESULT windowProcInternal(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

  };
};