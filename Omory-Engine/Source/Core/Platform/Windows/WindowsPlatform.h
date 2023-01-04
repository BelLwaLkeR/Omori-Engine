#pragma once
#include <Type/SmartPtr.h>
#include <Core/Platform/APlatform.h>


namespace Omory
{

	//class Dx12Common
	//{
	//public:
	//	Dx12Common();
	//	~Dx12Common();
	//	Response Setup(const PlatformInfo& platformInfo, const HWND& windowHandler);
	//private:
	//	Response CreateDevice(ID3D12Device* device);
	//	Response CreateFactory(IDXGIFactory6* dxgiFactory);



	//private:
	//	ID3D12Device* _device = nullptr;
	//	IDXGIFactory6* _dxgiFactory = nullptr;
	//	ID3D12CommandQueue* _cmdQueue = nullptr;
	//	IDXGISwapChain4* _swapChain = nullptr;
	//	ID3D12CommandAllocator* _cmdAllocator = nullptr;
	//	ID3D12GraphicsCommandList* _cmdList = nullptr;




	//};
	class Dx12Common;
	class WindowsContent;

	class WindowsPlatform:public APlatform
	{
	public:

		WindowsPlatform(const std::string& title, int width, int height, int targetFps);
		~WindowsPlatform();
		// APlatform ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
		virtual Response CreateDevice() override;
		virtual Response LoopDevide() override;
		virtual Response Shutdown() override;
		virtual Response UpdatePlatformInfo() override;

		//static LPCWSTR Str2LpCWstr(const std::string& str);
		//static RECT Rectangle2RECT(const Rectangle& rectangle);
		
	private:
		UniquePtr<WindowsContent> content = nullptr;
		UniquePtr<Dx12Common> dx12Common = nullptr;
		Response CreateGameWindow();
		Response CreateDx12Device();
	};
}