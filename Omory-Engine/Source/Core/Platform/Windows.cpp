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

Omory::Response Omory::Windows::LoopDevide()
{
  if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) == FALSE) {
    return { EResponseCode::S01_Continue };
  }

  TranslateMessage(&message);
  DispatchMessage(&message);

  if (message.message == WM_QUIT) {
    return { EResponseCode::S00_Success };
  }
  return { EResponseCode::S01_Continue };
}

Omory::Response Omory::Windows::CreateDevice()
{
  hInstance = GetModuleHandle(nullptr);
  if (hInstance == nullptr) { return { EResponseCode::E00_AnythingError, "モジュールハンドルが取得できませんでした。" }; }

  wndClassEx = {};
  wndClassEx.cbSize = sizeof(WNDCLASSEX);
  wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
  wndClassEx.lpfnWndProc = WindowsProcedure;
  wndClassEx.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
  wndClassEx.hCursor = LoadCursor(hInstance, IDC_ARROW);
  wndClassEx.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
  wndClassEx.lpszMenuName = nullptr;
  wndClassEx.lpszClassName = TEXT("hogefuga");
  //wndClassEx.lpszClassName = Str2LpCWstr(platformInfo.appName);
  wndClassEx.hInstance = hInstance;
  if (!RegisterClassEx(&wndClassEx)) {
    return { EResponseCode::E00_AnythingError, "ウィンドウクラスが登録できませんでした。" };
  }

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
  if (hWindow == nullptr) { return { EResponseCode::E21_ApplicationShutdownError, "ウィンドウハンドラがnullptrになりました。" }; }
  ShowWindow(hWindow, SW_SHOWNORMAL);
  UpdateWindow(hWindow);
  SetFocus(hWindow);
  message = {};



  return { EResponseCode::S01_Continue };
}

Omory::Response Omory::Windows::Shutdown()
{
  if (hInstance != nullptr) { UnregisterClass(wndClassEx.lpszClassName, hInstance); }
  hInstance = nullptr;
  hWindow = nullptr;
  PostQuitMessage(0);
  return { EResponseCode::S00_Success };
}

Omory::Response Omory::Windows::UpdatePlatformInfo()
{
  return Response();
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
