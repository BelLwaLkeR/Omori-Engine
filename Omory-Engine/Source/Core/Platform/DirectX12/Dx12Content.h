#pragma once

struct ID3D12Device;
struct IDXGIFactory6;
struct ID3D12CommandQueue;
struct IDXGISwapChain4;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
namespace Omory {
  class Dx12Content
  {
  public:
    ID3D12Device* device;
    IDXGIFactory6* dxgiFactory;
    ID3D12CommandQueue* cmdQueue;
    IDXGISwapChain4* swapChain;
    ID3D12CommandAllocator* cmdAllocator;
    ID3D12GraphicsCommandList* cmdList;
  };

}