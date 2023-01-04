#pragma once
#include <string>
#include <Type/Rectangle.h>

namespace Omory{
	class PlatformInfo
	{
		public:
		PlatformInfo(const Rectangle& screenRectangle, int targetFPS, const std::string& title, const std::string& appName)
		:screenRectangle(screenRectangle), targetFPS(targetFPS), title(title), appName(appName){}
		Rectangle screenRectangle;
		int targetFPS;
		std::string title;
		std::string appName;
	};
}