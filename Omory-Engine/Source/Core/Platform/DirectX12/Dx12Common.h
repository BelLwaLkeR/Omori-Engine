#pragma once
#include <Type/Response.h>
#include <Type/SmartPtr.h>
//#include <Core/Platform/PlatformInfo.h>


class PlatformInfo;
class WindowsContent;
class Dx12Content;

namespace Omory{
  class Dx12Common
  {
  public:
    Dx12Common();
    Dx12Common(const Dx12Common&);
    ~Dx12Common();
    //Response Setup(const PlatformInfo& platformInfo, const WindowsContent& windowsContent);
  private:
   Response CreateDevice();
   Response CreateFactory();
   


  private:
    UniquePtr<Dx12Content> content;
  };
}

