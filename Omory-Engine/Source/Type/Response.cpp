#include "Response.h"
#include <Core/Debug.h>

Omory::Response::Response()
  :responseCode(EResponseCode::O90_Undefined),message("")
{}

Omory::Response::Response(EResponseCode code, const std::string& message)
  :responseCode(code), message(message)
{
  Debug::getInstance()->Print(*this);
}

Omory::EResponseCodeHead Omory::Response::GetCodeHead() const
{
  {
    int headNum = static_cast<int>(responseCode) / pow(10,RESPONSE_CODE_DIGITS-1);
    return static_cast<EResponseCodeHead>(headNum);
  }
}

bool Omory::Response::IsOverWarningLevel(EResponseCodeHead thresholdLevel) const
{
  int threshold = static_cast<int>(thresholdLevel);
  int level = static_cast<int>(GetCodeHead());
  return level >= threshold;
}

std::string Omory::Response::ToString() const
{

  return "CODE:["+ std::to_string(static_cast<int>(responseCode))+"] "+"\"" + message + "\"";
}
