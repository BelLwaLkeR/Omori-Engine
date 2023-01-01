#pragma once
#include <string>

namespace Omory {

  /// <summary>
  /// ���X�|���X�R�[�h�ڍׂ͊e�R�����g��
  /// </summary>
  enum class EResponseCode
  {

    // ���s
    //I00_Continue            = 100,

    // ����
    S00_Success             = 100,
    // ���s
    S01_Continue            = 101,

    // �����̃G���[
    E00_AnythingError       = 200,
    // �f�o�C�X�̉����̃G���[
    E10_DeviceAnythingError = 210,
    // �A�v���P�[�V�����̉����̃G���[
    E20_ApplicationAnythingError = 210,
    // �A�v���P�[�V�����̉����̃G���[
    E21_ApplicationShutdownError = 210,

    // �����̌x��
    W00_AnythingWorning     = 300,
    // �f�o�C�X�̉����̌x��
    W10_DeviceAnythingError = 310,
    // ����`
    O90_Undefined           = 900,
    _END_
  };

  /// <summary>
  /// �����R�[�h�̌���
  /// </summary>
  const int RESPONSE_CODE_DIGITS = 3;

  /// <summary>
  /// EResponseCode�̓���������A�T�v���擾����
  /// </summary>
  enum class EResponseCodeHead
  {
    Success     = 1,
    Error       = 2,
    Worning     = 3,
    Other       = 9,
  };

  /// <summary>
  /// �����N���X�B�G���[�R�[�h�ɂ��T�v�ƁA���b�Z�[�W�ɂ��ڍׂ��p�b�P�[�W��
  /// </summary>
  class Response
  {
  public:
  // �f�t�H���g�R���X�g���N�^�ł͖���`���b�Z�[�W��Ԃ��B
    Response();
  
  // �����R�[�h�����B
    Response(EResponseCode code, const std::string& message = "");

    EResponseCode responseCode = EResponseCode::O90_Undefined;
    std::string message = "";

    /// <summary>
    /// �����R�[�h����ǂ̎�ނ̉��������擾����
    /// </summary>
    /// <returns>�����̎��</returns>
    EResponseCodeHead GetCodeHead() const;
    bool IsSuccess() const;
    bool IsFailed() const;
    bool IsOverWarningLevel(EResponseCodeHead thresholdLevel) const;
    bool IsLowerWarningLevel(EResponseCodeHead thresholdLevel) const;
    std::string ToString() const;
  };
}