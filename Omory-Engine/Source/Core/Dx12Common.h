#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")


class Dx12Common
{
public:
  Dx12Common();
  ~Dx12Common();
  bool Setup();
private:
   
private:
  ID3D12Device* _device;
  IDXGIFactory6* _dxgiFactory;
  IDXGISwapChain4* _swapChain;




};
