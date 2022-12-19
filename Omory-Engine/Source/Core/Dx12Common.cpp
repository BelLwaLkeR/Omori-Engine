#include "Dx12Common.h"
#include <vector>
#include <functional>
#include <iostream>

Dx12Common::Dx12Common()
{
}

Dx12Common::~Dx12Common()
{
}

bool Dx12Common::Setup()
{
  _device = nullptr;
  _dxgiFactory = nullptr;
  _swapChain = nullptr;
  HRESULT result; 

  D3D_FEATURE_LEVEL featureLevels[] =
  {
//    D3D_FEATURE_LEVEL_12_2,
    D3D_FEATURE_LEVEL_12_1,
    D3D_FEATURE_LEVEL_12_0,
    D3D_FEATURE_LEVEL_11_1,
    D3D_FEATURE_LEVEL_11_0,
  };

  for(auto fl:featureLevels){
    result = D3D12CreateDevice(
      nullptr, 
      fl,
      IID_PPV_ARGS(&_device)
    );
    if(result == S_OK){ break; }
  }
  if(_device == nullptr){ return false; }
  
  result = CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory));
  std::vector<IDXGIAdapter*> adapters;
  IDXGIAdapter* tmpAdapter = nullptr;
  for (int i = 0; i < _dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
  {
    adapters.push_back(tmpAdapter);
  }
  if(_dxgiFactory == nullptr){ return false; }

  return true;
}

