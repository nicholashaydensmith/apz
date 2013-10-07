#include "stdafx.h"
#include "apzWindow.h"
#include "apzUtilities.h"

using namespace apz;

//  Initialize static variables
int Window::m_id = 0;
std::map<HWND, Window *> Window::m_windowMap;

Window::Window(const char *tName, int tX, int tY, int tWidth, int tHeight) 
  : m_windowName(tName)
  , m_windowClassName("Window")
  , m_x(tX)
  , m_y(tY)
  , m_width(tWidth)
  , m_height(tHeight)
  , m_renderer(NULL)
{

  m_win.m_hRC = NULL;
  m_win.m_hDC = NULL;
  m_win.m_hWnd = NULL;
  m_win.m_hInstance = NULL;

  std::stringstream stringStream;
  stringStream << m_windowClassName << " " << m_id++;

  m_windowClassName = stringStream.str();

  m_winActive = true;

}

void Window::Initialize() {
  winInit();
}

void Window::winInit() {


  GLuint		pixelFormat;                              // Holds The Results After Searching For A Match
  WNDCLASS	windowClass;                              // Windows Class Structure

  m_win.m_hInstance	= GetModuleHandle(NULL);                // Grab An Instance For Our Window

  ZeroMemory(&windowClass, sizeof(WNDCLASS));
  windowClass.style			    = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	  // Redraw On Move, And Own DC For Window
  windowClass.lpfnWndProc		= (WNDPROC)&Window::windowProc;   // WindowProc Handles Messages
  windowClass.cbClsExtra		= 0;									                  // No Extra Window Data
  windowClass.cbWndExtra		= 0;                                    // No Extra Window Data
  windowClass.hInstance		    = m_win.m_hInstance;                          // Set The Instance
  windowClass.hCursor		    = LoadCursor(NULL, IDC_ARROW);          // Load The Arrow Pointer
  windowClass.hbrBackground	    = NULL;                                 // No Background Required For GL
  windowClass.lpszMenuName	    = NULL;                                 // We Don't Want A Menu
  windowClass.lpszClassName	    = m_windowClassName.c_str();            // Set The Class Name
  windowClass.hIcon             = (HICON)LoadImage(NULL, "Infinite_Z.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);

  // Attempt To Register The Window Class
  if (!RegisterClass(&windowClass))
  {
    MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return;
  }

  m_win.m_hWnd = CreateWindowEx(NULL,                               // Extended Style For The Window
    m_windowClassName.c_str(),          // Class Name
    m_windowName.c_str(),               // Window Title
    WS_OVERLAPPEDWINDOW |
    WS_CLIPCHILDREN     |
    WS_CLIPSIBLINGS,
    m_x, m_y,                           // Window Position
    m_width,                            // Window Width
    m_height,                           // Window Height
    NULL,                               // No Parent Window
    NULL,                               // No Menu
    m_win.m_hInstance,                        // Instance
    NULL);

  if (!m_win.m_hWnd)								        
  {
    winKill();											      
    MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return;
  }

  // <SampleCode PixelFormatDescriptor Setup>
  // Set the appropriate pixel format.
  PIXELFORMATDESCRIPTOR pfd =					
  {
    sizeof(PIXELFORMATDESCRIPTOR),            // Size Of This Pixel Format Descriptor
    1,                                        // Version Number
    PFD_DRAW_TO_WINDOW |                      // Format Must Support Window
    PFD_SUPPORT_OPENGL |                      // Format Must Support OpenGL
    PFD_STEREO         |                      // Format Must Support Quad-buffer Stereo
    PFD_DOUBLEBUFFER,                         // Must Support Double Buffering
    PFD_TYPE_RGBA,                            // Request An RGBA Format
    24,                                       // 24-bit color depth
    0, 0, 0, 0, 0, 0,                         // Color Bits Ignored
    0,                                        // No Alpha Buffer
    0,                                        // Shift Bit Ignored
    0,                                        // No Accumulation Buffer
    0, 0, 0, 0,                               // Accumulation Bits Ignored
    32,                                       // 32-bit Z-Buffer (Depth Buffer)
    0,                                        // No Stencil Buffer
    0,                                        // No Auxiliary Buffer
    PFD_MAIN_PLANE,                           // Main Drawing Layer
    0,                                        // Reserved
    0, 0, 0                                   // Layer Masks Ignored
  };
  // </SampleCode PixelFormatDescriptor Setup>

  // Did We Get A Device Context?
  if (!(m_win.m_hDC = GetDC(m_win.m_hWnd)))								
  {
    winKill();											      
    MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
    return;
  }

  // Did Windows Find A Matching Pixel Format?
  if (!(pixelFormat = ChoosePixelFormat(m_win.m_hDC, &pfd)))	
  {
    winKill();											     
    MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return;
  }

  // Are We Able To Set The Pixel Format?
  if (!SetPixelFormat(m_win.m_hDC, pixelFormat, &pfd))	
  {
    winKill();											    
    MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return;
  }

  // Are We Able To Get A Rendering Context?
  if (!(m_win.m_hRC = wglCreateContext(m_win.m_hDC)))			
  {
    winKill();											      
    MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return;
  }

  // Try To Activate The Rendering Context.
  if (!wglMakeCurrent(m_win.m_hDC, m_win.m_hRC))								
  {
    winKill();											     
    MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
    return;
  }

  ShowWindow(m_win.m_hWnd, SW_SHOW);                // Show The Window
  SetForegroundWindow(m_win.m_hWnd);                // Slightly Higher Priority
  SetFocus(m_win.m_hWnd);                           // Sets Keyboard Focus To The Window

  // Add this OpenGlWindow to the window map so that we can access the correct
  // OpenGlWindow (based on hWnd) from the static windowProc method.
  m_windowMap[m_win.m_hWnd] = this;

  if(!m_renderer){
    winKill();
    MessageBox(NULL, "Window does not have a valid Renderer.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
    return;
  }

  m_renderer->Setup(m_x, m_y, m_width, m_height);

  m_winActive = false;
}

void Window::winKill()
{
  // Do We Have A Rendering Context?
  if (m_win.m_hRC)													          
  {
    // Are We Able To Release The DC And RC Contexts?
    if (!wglMakeCurrent(NULL, NULL))						
      MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

    // Are We Able To Delete The RC?
    if (!wglDeleteContext(m_win.m_hRC))								
      MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

    m_win.m_hRC = NULL;												        
  }

  // Are We Able To Release The DC?
  if (m_win.m_hDC)				
  {
    if (!ReleaseDC(m_win.m_hWnd, m_win.m_hDC))
      MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

    m_win.m_hDC = NULL;
  }

  // Are We Able To Destroy The Window?
  if (m_win.m_hWnd)					
  {
    if (!DestroyWindow(m_win.m_hWnd))
      MessageBox(NULL, "Could Not Release hWnd.","SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

    m_win.m_hWnd = NULL;	
  }

  // Are We Able To Unregister Class?
  if (m_win.m_hInstance)
  {
    if (!UnregisterClass(m_windowClassName.c_str(), m_win.m_hInstance))
      MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

    m_win.m_hInstance = NULL;
  }

  if(m_renderer) m_renderer->Kill();


}


Window::~Window() {
  winKill();
}

WINDOW_DATA *Window::getWindowData() {
  return &m_win;
}

int Window::getX() const {
  return m_x;
}

int Window::getY() const {
  return m_y;
}

int Window::getWidth() const {
  return m_width;
}

int Window::getHeight() const {
  return m_height;
}

HGLRC     Window::getRenderingContext() const {
  return m_win.m_hRC;
}

HDC       Window::getDeviceContext() const {
  return m_win.m_hDC;
}

HWND      Window::getWindowHandle() const {
  return m_win.m_hWnd;
}

HINSTANCE Window::getApplicationInstance() const {
  return m_win.m_hInstance;
}

void Window::BeginEventLoop() {

  if(m_winActive){
    CRITICAL_ERROR("Window not yet initialized");
  }

  m_winActive = true;

  /*  Must be called within the loop  */
  MSG msg;
  while (m_winActive)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    // If 'escape' was pressed, exit the application.
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000){
      PostMessage(m_win.m_hWnd, WM_DESTROY, 0, 0);
      m_winActive = false;
    }


    if(m_renderer){
      m_renderer->Render();
    }

  }

  winKill();
}

Renderer *Window::GetRenderer() {
  return m_renderer;
}

void Window::SetRenderer(Renderer *tRenderer) {
  m_renderer = tRenderer;
}

LRESULT CALLBACK Window::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  Window* win = m_windowMap[hWnd];

  // Call the window proc for the OpenGlWindow if valid.
  if (win) 
    return win->windowProcInternal(hWnd, message, wParam, lParam); 

  // If the OpenGlWindow is not valid, call the default window proc.
  return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT Window::windowProcInternal(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg)
  {
  case WM_CLOSE:
    {
      m_winActive = false;
      return 0;
    }
  case WM_DESTROY:
    {
      PostQuitMessage(0);
      return 0;
    } 
  case WM_SHOWWINDOW:
  case WM_SIZE:
    {
      RECT rect;
      if (GetClientRect(hWnd, &rect))
      {
        m_width = rect.right-rect.left;
        m_height = rect.bottom-rect.top;
        if(m_renderer) m_renderer->Resize(m_width, m_height, m_x, m_y);
      }
      return 0;
    } 
  case WM_MOVE:
    {
      RECT rect;
      if (GetClientRect(hWnd, &rect))
      {
        m_width = rect.right-rect.left;
        m_height = rect.bottom-rect.top;
        if(m_renderer) m_renderer->Resize(m_width, m_height, m_x, m_y);
      }
      m_x = (int)(short)LOWORD(lParam);
      m_y = (int)(short)HIWORD(lParam);
      return 0;
    }
  case WM_KEYDOWN:
    {
      return 0;
    }
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}