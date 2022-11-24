#include <Windows.h>
#include <tchar.h>
#include <Omory-Engine/Source/Core/Dx12Common.h>

#ifdef _DEBUG
#include <iostream>
#endif


using namespace std; 

void DebugOutputFormatString(const char* format, ...)
{
  #ifdef _DEBUG
  va_list valist;
  va_start (valist, format);
  printf(format, valist);
  va_end(valist);
  #endif

}

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  if(msg == WM_DESTROY)
  {
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hwnd, msg, wparam, lparam); 
}

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif // _DEBUG
{
  WNDCLASSEX w = {};
  w.cbSize = sizeof(WNDCLASSEX
  );
  w.lpfnWndProc = (WNDPROC)WindowProcedure;
  w.lpszClassName = _T("Dx12Sample");
  w.hInstance = GetModuleHandle(nullptr);

  static const int window_width = 1024;
  static const int window_height = 720;



  RegisterClassEx(&w);
  RECT wrc = {0, 0, window_width, window_height};
  AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

  HWND hwnd = CreateWindow(
    w.lpszClassName,
    _T("DX12Test"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    wrc.right - wrc.left,
    wrc.bottom - wrc.top,
    nullptr,
    nullptr,
    w.hInstance,
    nullptr
  );

  ShowWindow(hwnd, SW_SHOW);

  Dx12Common* dx12Common = new Dx12Common();
  bool result = dx12Common->Setup();
  if(!result){ 
    delete dx12Common;
    return 0;
  }


  MSG msg = {};
  while(true)
  {
    if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    if (msg.message == WM_QUIT) { break; }
  }

  UnregisterClass(w.lpszClassName, w.hInstance);
  delete dx12Common;

  return 0;
}
