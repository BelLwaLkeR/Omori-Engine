#pragma once
#include <Source/Core/Platform/PlatformInfo.h>
#include <Source/Type/Response.h>

namespace Omory
{
	class APlatform
	{
	public:
		APlatform(const PlatformInfo& platformInfo):platformInfo(platformInfo){}
		virtual Response CreateDevice()				= 0;
		virtual Response LoopDevide()					= 0;
		virtual Response Shutdown()						= 0;
		virtual Response UpdatePlatformInfo() = 0;
		PlatformInfo platformInfo;
	};
}