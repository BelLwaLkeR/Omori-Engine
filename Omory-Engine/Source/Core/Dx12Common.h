#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <Type/Response.h>
#include <Core/Platform/PlatformInfo.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace Omory{
  class Dx12Common
  {
  public:
    Dx12Common();
    ~Dx12Common();
    Response Setup(const PlatformInfo& platformInfo, const HWND& windowHandler);
  private:
   Response CreateDevice(ID3D12Device* device);
   Response CreateFactory(IDXGIFactory6* dxgiFactory);


  private:
    ID3D12Device* _device = nullptr;
    IDXGIFactory6* _dxgiFactory = nullptr;
    ID3D12CommandQueue* _cmdQueue = nullptr;
    IDXGISwapChain4* _swapChain = nullptr;
    ID3D12CommandAllocator* _cmdAllocator = nullptr;
    ID3D12GraphicsCommandList* _cmdList = nullptr;




  };
}