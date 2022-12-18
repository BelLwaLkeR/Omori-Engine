#include <Windows.h>
#include <Application.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Omory::Application app;
  app.Run();
  return 0;
}