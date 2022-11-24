#pragma once
#include <string>

namespace Omory {
  enum class EResponseCode
  {
    I00_Continue = 0,
    S00_Success = 100,
    E00_AnythingError = 200,
    E10_DeviceAnythingError,
    W00_AnythingWorning = 300,
    W10_DeviceAnythingError,
    _END_
  };
  enum class EResponseCodeHead
  {
    Infomation = 0,
    Success = 1,
    Error = 2,
    Worning = 3,
  };

  class Response
  {
  public:
    Response(EResponseCode code, const std::string& message = "")
      :resCode(code), message(message) {}
    EResponseCode resCode;
    std::string message;
    EResponseCodeHead GetCodeHead()
    {
      int headNum = static_cast<int>(resCode) / 100;
      return static_cast<EResponseCodeHead>(headNum);
    }
  };
}