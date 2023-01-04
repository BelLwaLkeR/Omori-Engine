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
		static LRESULT CALLBACK WindowsProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){ return 0; }
	private:

	};
}