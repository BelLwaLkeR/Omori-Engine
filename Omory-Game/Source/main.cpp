#include "../../Omory-Engine/Source/Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Omory::System::Application* app = new Omory::System::Application();
  app->ApplicationMain();
  delete app;

  return 0;
}
