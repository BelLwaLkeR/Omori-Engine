#include "WindowsPlatform.h"
#include <Core/Platform/DirectX12/Dx12Common.h>
#include <Core/Platform/PlatformInfo.h>
#include <Core/Platform/Windows/WindowsContent.h>
#include <Windows.h>


//LRESULT Omory::WindowsPlatform::WindowsProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//  if (msg == WM_DESTROY)
//  {
//    PostQuitMessage(0);
//    return 0;
//  }
//  return DefWindowProc(hwnd, msg, wparam, lparam);
//}

Omory::WindowsPlatform::WindowsPlatform(const std::string& title, int width, int height, int targetFps)
  :APlatform({{0, 0, width, height}, targetFps, title, title})
{
  content = MakeUnique<WindowsContent>();
}

Omory::WindowsPlatform::~WindowsPlatform() = default;

Omory::Response Omory::WindowsPlatform::CreateGameWindow()
{
  content->hInstance = GetModuleHandle(nullptr);
  if (content->hInstance == nullptr) { return { EResponseCode::E00_AnythingError, "モジュールハンドルが取得できませんでした。" }; }

  content->wndClassEx = {};
  content->wndClassEx.cbSize = sizeof(WNDCLASSEX);
  content->wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
  content->wndClassEx.lpfnWndProc = content->WindowsProcedure;
  content->wndClassEx.hIcon = LoadIcon(content->hInstance, IDI_APPLICATION);
  content->wndClassEx.hCursor = LoadCursor(content->hInstance, IDC_ARROW);
  content->wndClassEx.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
  content->wndClassEx.lpszMenuName = nullptr;
  content->wndClassEx.lpszClassName = TEXT("hogefuga");
  //wndClassEx.lpszClassName = Str2LpCWstr(platformInfo.appName);
  content->wndClassEx.hInstance = content->hInstance;
  if (!RegisterClassEx(&(content->wndClassEx))) {
    return { EResponseCode::E00_AnythingError, "ウィンドウクラスが登録できませんでした。" };
  }

  RECT rect = 
  {
    static_cast<LONG>(platformInfo.screenRectangle.left),
    static_cast<LONG>(platformInfo.screenRectangle.top),
    static_cast<LONG>(platformInfo.screenRectangle.right),
    static_cast<LONG>(platformInfo.screenRectangle.bottom),
  };

  auto wndStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
  AdjustWindowRect(&rect, wndStyle, false);


  content->hWindow = CreateWindowEx(
    0,
    content->wndClassEx.lpszClassName,
    TEXT("HogeFUga"),
    wndStyle,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    platformInfo.screenRectangle.width(),
    platformInfo.screenRectangle.height(),
    nullptr,
    nullptr,
    content->hInstance,
    nullptr);
  if (content->hWindow == nullptr) { return { EResponseCode::E21_ApplicationShutdownError, "ウィンドウハンドラがnullptrになりました。" }; }
  return { EResponseCode::S00_Success };
}

Omory::Response Omory::WindowsPlatform::CreateDx12Device()
{
  //dx12Common = MakeUnique<Dx12Common>();
  //dx12Common->Setup(platformInfo,hWindow);
  return Response();
}

Omory::Response Omory::WindowsPlatform::LoopDevide()
{
  if (PeekMessage(&(content->message), nullptr, 0, 0, PM_REMOVE) == FALSE) {
    return { EResponseCode::S01_Continue };
  }

  TranslateMessage(&(content->message));
  DispatchMessage(&(content->message));

  if (content->message.message == WM_QUIT) {
    return { EResponseCode::S00_Success };
  }
  return { EResponseCode::S01_Continue };
}



Omory::Response Omory::WindowsPlatform::CreateDevice()
{
  Response response;
  response = CreateGameWindow();
  if(response.IsFailed()){ return response; }
  


  ShowWindow(content->hWindow, SW_SHOWNORMAL);
  UpdateWindow(content->hWindow);
  SetFocus(content->hWindow);
  content->message = {};
  return { EResponseCode::S01_Continue };
}

Omory::Response Omory::WindowsPlatform::Shutdown()
{
  if (content->hInstance != nullptr) { UnregisterClass(content->wndClassEx.lpszClassName, content->hInstance); }
  content->hInstance = nullptr;
  content->hWindow = nullptr;
  PostQuitMessage(0);
  return { EResponseCode::S00_Success };
}

Omory::Response Omory::WindowsPlatform::UpdatePlatformInfo()
{
  return Response();
}

//LPCWSTR Omory::WindowsPlatform::Str2LpCWstr(const std::string& str)
//{
//  int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);
//  wchar_t* wc = new wchar_t[size];
//  MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wc, 0);
//  std::wstring wstr(wc, wc + size - 1);
//  delete[] wc;
//  return wstr.c_str();
//}

//RECT Omory::WindowsPlatform::Rectangle2RECT(const Rectangle& rectangle)
//{
//  return {
//    static_cast<LONG>(rectangle.left),
//    static_cast<LONG>(rectangle.top),
//    static_cast<LONG>(rectangle.right),
//    static_cast<LONG>(rectangle.bottom),
//  };
//}
