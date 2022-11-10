#pragma once
#include <Windows.h>
#include <string>

namespace Omory::System {
    class Application
    {
    public:
      enum class EApplicationCallback
      {
        RUNNING,
        EXIT,
        _END_
      };

    public:
      Application();
      ~Application();
      EApplicationCallback ApplicationMain();

    private:

    };

  }