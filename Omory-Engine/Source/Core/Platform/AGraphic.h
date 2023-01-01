#pragma once
#include <Core/Platform/APlatform.h>

namespace Omory
{
  class AGraphic
  {
  public:
    AGraphic(APlatform* platform);
  private:
    APlatform* platform;
  };
}


template<class T>
concept Drawable = requires(T& x)
{
  x.draw();
}
