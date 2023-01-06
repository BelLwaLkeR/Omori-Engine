#pragma once
#include <Type/Response.h>
#include <Type/SmartPtr.h>

namespace Omory {
  class PlatformInfo;
  class WindowsContent;
  class Dx12Content;

  class Dx12Common
  {
  public:
    Dx12Common();
    Dx12Common(const Dx12Common&);
    ~Dx12Common();
    Response Setup(const PlatformInfo& platformInfo, WeakPtr<WindowsContent> windowsContent);
//    Response Setup( WindowsContent* windowsContent);
  private:
    Response CreateDevice();
    Response CreateFactory();



  private:
    UniquePtr<Dx12Content> content;
  };
}

