#pragma once
#include <Windows.h>
#include <string>
#include <Source/Core/Platform/APlatform.h>
namespace Omory{
  class Application
  {
  public:
    Application();
    ~Application();
    EApplicationCallback CreateDevice();
    EApplicationCallback Initialize();
    EApplicationCallback Update();
    void Shutdown();
    void Run();

  private:
    APlatform* platform;
  };
}
