#pragma once
#include <string>
#include <Core/Singleton.h>
#include <Type/Response.h>

namespace Omory
{
	class Debug:public Singleton<Debug>
	{
	public:
		Debug(){}
		~Debug(){}
		void Print(const std::string& message);
		void Print(const Omory::Response& response, bool assert = false, Omory::EResponseCodeHead assertThreshold = Omory::EResponseCodeHead::Other);


	private:

	};
}