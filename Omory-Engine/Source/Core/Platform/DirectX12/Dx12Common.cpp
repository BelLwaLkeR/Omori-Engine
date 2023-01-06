#include "Dx12Common.h"

#include <vector>
#include <functional>
#include <iostream>
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <Core/Platform/PlatformInfo.h>
#include <Core/Platform/Windows/WindowsContent.h>
#include <Core/Platform/DirectX12/Dx12Content.h>

Omory::Dx12Common::Dx12Common()
{
  content = MakeUnique<Dx12Content>();

}

Omory::Dx12Common::Dx12Common(const Dx12Common& copy)
{
  content = MakeUnique<Dx12Content>();
}

Omory::Dx12Common::~Dx12Common() = default;

Omory::Response Omory::Dx12Common::Setup(const PlatformInfo& platformInfo, WeakPtr<WindowsContent> windowsContent)
{

  if(CreateDevice(). IsFailed() ){ return { EResponseCode::E00_AnythingError}; }
  if(CreateFactory().IsFailed() ){ return { EResponseCode::E00_AnythingError}; }


  HRESULT result;

  //コマンドアロケータの作成
  result = content->device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&(content->cmdAllocator)));
  if(result != S_OK){ return { EResponseCode::E10_DeviceAnythingError, "コマンドアロケータの作成に失敗しました"}; }

  result = content->device->CreateCommandList(
    0, 
    D3D12_COMMAND_LIST_TYPE_DIRECT,
    content->cmdAllocator,
    nullptr,
    IID_PPV_ARGS(&(content->cmdList))
  );
  if(result != S_OK){ return { EResponseCode::E10_DeviceAnythingError, "コマンドアロケータの作成に失敗しました"}; }


  // コマンドキューの作成
  D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
  cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  cmdQueueDesc.NodeMask = 0;
  cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
  cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  result = content->device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&(content->cmdQueue)));
  if(result != S_OK){ return { EResponseCode::E10_DeviceAnythingError, "CommandQueueの作成に失敗しました。"}; }

  // スワップチェインの作成
  DXGI_SWAP_CHAIN_DESC1 scDesc = {};
  scDesc.Width =  platformInfo.screenRectangle.width();
  scDesc.Height = platformInfo.screenRectangle.height();
  scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  scDesc.Stereo = false;
  scDesc.SampleDesc.Count = 1;
  scDesc.SampleDesc.Quality = 0;
  scDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
  scDesc.BufferCount = 2;

  scDesc.Scaling = DXGI_SCALING_STRETCH;
  scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  scDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
  scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
  result = content->dxgiFactory->CreateSwapChainForHwnd(
    content->cmdQueue,
    windowsContent->hWindow,
    &scDesc,
    nullptr,
    nullptr,
    (IDXGISwapChain1**)&(content->swapChain)
  );
  if(result != S_OK){ return { EResponseCode::E10_DeviceAnythingError, "SwapChainの作成に失敗しました。" }; }

  // デスクリプタヒープの作成
  D3D12_DESCRIPTOR_HEAP_DESC descHeap = {};
  descHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  descHeap.NodeMask = 0;
  descHeap.NumDescriptors = 2;
  descHeap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

  ID3D12DescriptorHeap* rtvHeaps = nullptr;
  result = content->device->CreateDescriptorHeap(&descHeap, IID_PPV_ARGS(&rtvHeaps));
  auto dhHandle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
  auto dhHandleInclSize = content->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

  // デスクリプタヒープとスワップチェインの紐づけ
  DXGI_SWAP_CHAIN_DESC swcDesc = {};
  result = content->swapChain->GetDesc(&swcDesc);
  std::vector<ID3D12Resource*> backBuffers(swcDesc.BufferCount);
  for(UINT i = 0; i< swcDesc.BufferCount; i++)
  {
    result = content->swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i]));
    if(result != S_OK){ return{ EResponseCode::E10_DeviceAnythingError, "スワップチェインのバッファを取得できませんでした。" }; }
    dhHandle.ptr += dhHandleInclSize * i;
    content->device->CreateRenderTargetView(
      backBuffers[i],
      nullptr,
      dhHandle
    );
  }


  return { EResponseCode::S00_Success };
}




Omory::Response Omory::Dx12Common::CreateDevice()
{
  HRESULT result;
  D3D_FEATURE_LEVEL featureLevels[] =
  {
    D3D_FEATURE_LEVEL_12_2,
    D3D_FEATURE_LEVEL_12_1,
    D3D_FEATURE_LEVEL_12_0,
    D3D_FEATURE_LEVEL_11_1,
    D3D_FEATURE_LEVEL_11_0,
  };

  for(auto fl:featureLevels){
    result = D3D12CreateDevice(
      nullptr, 
      fl,
      IID_PPV_ARGS(&(content->device))
    );
    if(result == S_OK){ break; }
  }
  if(content->device == nullptr){ return { EResponseCode::E10_DeviceAnythingError, "デバイスの作成に失敗しました。" }; }

  return { EResponseCode::S00_Success };
}

Omory::Response Omory::Dx12Common::CreateFactory()
{
  HRESULT result = CreateDXGIFactory1(IID_PPV_ARGS(&(content->dxgiFactory)));
  std::vector<IDXGIAdapter*> adapters;
  IDXGIAdapter* tmpAdapter = nullptr;
  for (int i = 0; i < content->dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
  {
    adapters.push_back(tmpAdapter);
  }
  if(content->dxgiFactory == nullptr){ return { EResponseCode::E10_DeviceAnythingError, "dxgiファクトリの作成に失敗しました。" }; }
   
  return { EResponseCode::S00_Success };
}

