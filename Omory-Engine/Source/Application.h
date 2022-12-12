#pragma once
#include <Windows.h>
#include <string>
#include <Source/Core/Platform/APlatform.h>
#include <Source/Type/Response.h>
namespace Omory{
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
    APlatform* platform;
  };
}
