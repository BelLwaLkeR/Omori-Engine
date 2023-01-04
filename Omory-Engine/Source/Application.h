#pragma once
#include <Windows.h>
#include <string>
#include <Type/Response.h>
#include <Type/SmartPtr.h>
namespace Omory{

  class APlatform;

  class Application
  {
  public:
    Application();
    ~Application();
    Response CreateDevice();
    Response Initialize();
    Response Update();
    void Shutdown();
    void Run();

  private:
    UniquePtr<APlatform> platform;
  };
}
