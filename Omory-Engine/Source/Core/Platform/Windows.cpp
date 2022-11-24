#include "Windows.h"

LRESULT Omory::Windows::WindowsProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  if (msg == WM_DESTROY)
  {
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Omory::Windows::UpdatePlatformInfo()
{
}

Omory::Response Omory::Windows::LoopDevide()
{
  if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) == FALSE){ return Response::RUNNING; }

  TranslateMessage(&message);
  DispatchMessage(&message);
  
  if (message.message == WM_QUIT) { return Response::SHUTDOWN_SUCCESS; }
  return Response::RUNNING;
}


Omory::Response Omory::Windows::CreateDevice()
{
  hInstance = GetModuleHandle(nullptr);
  if (hInstance == nullptr) { return Response::SHUTDOWN_ERROR; }

  wndClassEx = {};
  wndClassEx.cbSize = sizeof(WNDCLASSEX);
  wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
  wndClassEx.lpfnWndProc = WindowsProcedure;
  wndClassEx.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
  wndClassEx.hCursor = LoadCursor(hInstance, IDC_ARROW);
  wndClassEx.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
  wndClassEx.lpszMenuName = nullptr;
  wndClassEx.lpszClassName = Str2LpCWstr(platformInfo.appName);
  wndClassEx.hInstance = GetModuleHandle(nullptr);
  if (!RegisterClassEx(&wndClassEx)) { 
    return Response::SHUTDOWN_ERROR; 
  };

  RECT rect = Rectangle2RECT(platformInfo.screenRectangle);
  auto wndStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
  AdjustWindowRect(&rect, wndStyle, false);


  hWindow = CreateWindowEx(
    0,
    wndClassEx.lpszClassName,
    Str2LpCWstr(platformInfo.title),
    wndStyle,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    platformInfo.screenRectangle.width(),
    platformInfo.screenRectangle.height(),
    nullptr,
    nullptr,
    hInstance,
    nullptr);
  if (hWindow == nullptr) { return Response::SHUTDOWN_ERROR; }
  ShowWindow(hWindow, SW_SHOWNORMAL);
  UpdateWindow(hWindow);
  SetFocus(hWindow);
  message = {};

  return Response::RUNNING;
}

void Omory::Windows::Shutdown()
{
  if(hInstance != nullptr){ UnregisterClass(wndClassEx.lpszClassName, hInstance); }
  hInstance = nullptr;
  hWindow = nullptr;
  PostQuitMessage(0);
}

LPCWSTR Omory::Windows::Str2LpCWstr(const std::string& str)
{
  int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);
  wchar_t* wc = new wchar_t[size];
  MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wc, 0);
  std::wstring wstr(wc, wc + size - 1);
  delete[] wc;
  return wstr.c_str();
}

RECT Omory::Windows::Rectangle2RECT(const Rectangle& rectangle)
{
  return {
    static_cast<LONG>(rectangle.left),
    static_cast<LONG>(rectangle.top),
    static_cast<LONG>(rectangle.right),
    static_cast<LONG>(rectangle.bottom),
  };
}
