#pragma once
#include <string>

namespace Omory {

  /// <summary>
  /// ���X�|���X�R�[�h�ڍׂ͊e�R�����g��
  /// </summary>
  enum class EResponseCode
  {
    // ����`
    O00_Undefined           = 0,

    // ���s
    //I00_Continue            = 100,

    // ����
    S00_Success             = 200,
    // ���s
    S01_Continue            = 201,

    // �����̃G���[
    E00_AnythingError       = 300,
    // �f�o�C�X�̉����̃G���[
    E10_DeviceAnythingError = 310,
    // �A�v���P�[�V�����̉����̃G���[
    E20_ApplicationAnythingError = 310,
    // �A�v���P�[�V�����̉����̃G���[
    E21_ApplicationShutdownError = 310,

    // �����̌x��
    W00_AnythingWorning     = 400,
    // �f�o�C�X�̉����̌x��
    W10_DeviceAnythingError = 410,
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
    Other       = 0,
    Infomation  = 1,
    Success     = 2,
    Error       = 3,
    Worning     = 4,
  };

  /// <summary>
  /// �����N���X�B�G���[�R�[�h�ɂ��T�v�ƁA���b�Z�[�W�ɂ��ڍׂ��p�b�P�[�W��
  /// </summary>
  class Response
  {
  public:
  // �f�t�H���g�R���X�g���N�^�ł͖���`���b�Z�[�W��Ԃ��B
    Response()
    :responseCode(EResponseCode::O00_Undefined), message("") {}
  
  // �����R�[�h�����B
    Response(EResponseCode code, const std::string& message = "")
    :responseCode(code), message(message) {}

    EResponseCode responseCode = EResponseCode::O00_Undefined;
    std::string message = "";

    /// <summary>
    /// �����R�[�h����ǂ̎�ނ̉��������擾����
    /// </summary>
    /// <returns>�����̎��</returns>
    EResponseCodeHead GetCodeHead()
    {
      int headNum = static_cast<int>(responseCode) / pow(10,RESPONSE_CODE_DIGITS-1);
      return static_cast<EResponseCodeHead>(headNum);
    }
  };
}