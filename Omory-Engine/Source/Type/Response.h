#pragma once
#include <string>

namespace Omory {

  /// <summary>
  /// レスポンスコード詳細は各コメントへ
  /// </summary>
  enum class EResponseCode
  {

    // 続行
    //I00_Continue            = 100,

    // 成功
    S00_Success             = 100,
    // 続行
    S01_Continue            = 101,

    // 何かのエラー
    E00_AnythingError       = 200,
    // デバイスの何かのエラー
    E10_DeviceAnythingError = 210,
    // アプリケーションの何かのエラー
    E20_ApplicationAnythingError = 210,
    // アプリケーションの何かのエラー
    E21_ApplicationShutdownError = 210,

    // 何かの警告
    W00_AnythingWorning     = 300,
    // デバイスの何かの警告
    W10_DeviceAnythingError = 310,
    // 未定義
    O90_Undefined           = 900,
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
    Success     = 1,
    Error       = 2,
    Worning     = 3,
    Other       = 9,
  };

  /// <summary>
  /// 応答クラス。エラーコードによる概要と、メッセージによる詳細をパッケージ化
  /// </summary>
  class Response
  {
  public:
  // デフォルトコンストラクタでは未定義メッセージを返す。
    Response();
  
  // 応答コードを代入。
    Response(EResponseCode code, const std::string& message = "");

    EResponseCode responseCode = EResponseCode::O90_Undefined;
    std::string message = "";

    /// <summary>
    /// 応答コードからどの種類の応答かを取得する
    /// </summary>
    /// <returns>応答の種類</returns>
    EResponseCodeHead GetCodeHead() const;
    bool IsSuccess() const;
    bool IsFailed() const;
    bool IsOverWarningLevel(EResponseCodeHead thresholdLevel) const;
    bool IsLowerWarningLevel(EResponseCodeHead thresholdLevel) const;
    std::string ToString() const;
  };
}