#pragma once
#include <Windows.h>
#include <Source/Core/Platform/APlatform.h>
#include <Source/Type/Response.h>

namespace Omory
{
	class Windows:public APlatform
	{
	public:
		Windows(const std::string& title, int width, int height, int targetFps)
			:APlatform({{0, 0, width, height}, targetFps, title, title}){}
		// APlatform ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
		virtual Response CreateDevice() override;
		virtual Response LoopDevide() override;
		virtual void Shutdown() override;
		static LPCWSTR Str2LpCWstr(const std::string& str);
		static RECT Rectangle2RECT(const Rectangle& rectangle);
		
	private:
		static LRESULT CALLBACK WindowsProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		HINSTANCE hInstance;
		WNDCLASSEX wndClassEx;
		HWND hWindow;
		MSG message;

		// APlatform ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
		virtual void UpdatePlatformInfo() override;
	};
}