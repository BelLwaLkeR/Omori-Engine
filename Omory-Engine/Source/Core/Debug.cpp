#include "Debug.h"
#include <assert.h>
#include <iostream>
#ifdef _DEBUG
#include <windows.h>
#endif // _DEBUG


void Omory::Debug::Print(const std::string& message)
{
#ifdef _DEBUG
  auto cMessage = message.c_str();
  OutputDebugStringA(cMessage);
#endif // _DEBUG
}

void Omory::Debug::Print(const Omory::Response& response, bool assert, Omory::EResponseCodeHead assertThreshold)
{
  if(assert)
  {
    assert(!response.IsOverWarningLevel(assertThreshold));
  }
  this->Print(response.ToString());

}
