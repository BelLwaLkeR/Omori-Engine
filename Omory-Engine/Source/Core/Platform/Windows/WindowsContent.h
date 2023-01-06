#pragma once
#include <Windows.h>

namespace Omory{
	class WindowsContent
	{
	public:
		WindowsContent();
		WindowsContent(const WindowsContent&);
		~WindowsContent();
		HINSTANCE hInstance;
		WNDCLASSEX wndClassEx;
		HWND hWindow;
		MSG message;
	private:

	};
}