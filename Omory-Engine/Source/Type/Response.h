#pragma once
#include <string>

namespace Omory {

  /// <summary>
  /// レスポンスコード詳細は各コメントへ
  /// </summary>
  enum class EResponseCode
  {
    // 未定義
    O00_Undefined           = 0,

    // 続行
    //I00_Continue            = 100,

    // 成功
    S00_Success             = 200,
    // 続行
    S01_Continue            = 201,

    // 何かのエラー
    E00_AnythingError       = 300,
    // デバイスの何かのエラー
    E10_DeviceAnythingError = 310,
    // アプリケーションの何かのエラー
    E20_ApplicationAnythingError = 310,
    // アプリケーションの何かのエラー
    E21_ApplicationShutdownError = 310,

    // 何かの警告
    W00_AnythingWorning     = 400,
    // デバイスの何かの警告
    W10_DeviceAnythingError = 410,
    _END_
  };

  /// <summary>
  /// 応答コードの桁数
  /// </summary>
  const int RESPONSE_CODE_DIGITS = 3;

  /// <summary>
  /// EResponseCodeの頭文字から、概要を取得する
  /// </summary>
  enum class EResponseCodeHead
  {
    Other       = 0,
    Infomation  = 1,
    Success     = 2,
    Error       = 3,
    Worning     = 4,
  };

  /// <summary>
  /// 応答クラス。エラーコードによる概要と、メッセージによる詳細をパッケージ化
  /// </summary>
  class Response
  {
  public:
  // デフォルトコンストラクタでは未定義メッセージを返す。
    Response()
    :responseCode(EResponseCode::O00_Undefined), message("") {}
  
  // 応答コードを代入。
    Response(EResponseCode code, const std::string& message = "")
    :responseCode(code), message(message) {}

    EResponseCode responseCode = EResponseCode::O00_Undefined;
    std::string message = "";

    /// <summary>
    /// 応答コードからどの種類の応答かを取得する
    /// </summary>
    /// <returns>応答の種類</returns>
    EResponseCodeHead GetCodeHead()
    {
      int headNum = static_cast<int>(responseCode) / pow(10,RESPONSE_CODE_DIGITS-1);
      return static_cast<EResponseCodeHead>(headNum);
    }
  };
}