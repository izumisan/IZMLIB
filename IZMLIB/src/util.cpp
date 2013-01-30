/*!
  @file  util.cpp
  @brief util���W���[���̎����t�@�C��
*/
#include <string>
#include <vector>

#include "util.h"

namespace izm
{

/*!
  @brief  ��������f���~�^�ŕ�������B
  @param  [in]  str        �������镶����
  @param  [in]  delimiter  �f���~�^ (�f�t�H���g����=" ")
  @return �������ꂽ������̃x�N�^
  @note   �A������f���~�^�͈�Ƃ݂Ȃ�\n
          (��) "abacdaaefga"��"a"�ŕ��������ꍇ�̖߂�l->{"b", "cd", "efg"}
*/
std::vector<std::string> split( const std::string& str, const std::string& delimiter )
{
    std::vector<std::string> result;
    std::string::size_type currentIdx = 0;
    std::string::size_type foundIdx = 0;

    while ( ( foundIdx = str.find( delimiter, currentIdx ) ) != std::string::npos )
    {
        if ( foundIdx != currentIdx )
        {
            result.push_back( str.substr( currentIdx, foundIdx - currentIdx ) );
            currentIdx = foundIdx + delimiter.size();
        }
        // �f���~�^���A�����Ă���ꍇ
        else
        {
            currentIdx += delimiter.size();
        }
    }
    // �c��̉��
    if ( currentIdx < str.size() )
    {
        result.push_back( str.substr( currentIdx, std::string::npos ) );
    }
    return result;
}

/*!
  @brief  �O��̋󔒗ޕ�����S�Ď�菜��
  @param  [in]  str  ������
  @return �O��̋󔒗ޕ�����S�Ď�菜����������
  @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u
*/
std::string trim( const std::string& str )
{
    std::string result( str );
    result = ltrim( result );
    result = rtrim( result );
    return result;
}

/*!
  @brief  �擪�̋󔒗ޕ�����S�Ď�菜��
  @param  [in]  str  ������
  @return �擪�̋󔒗ޕ�����S�Ď�菜����������
  @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u
*/
std::string ltrim( const std::string& str )
{
    // �󔒗ޕ����ł͂Ȃ��ŏ��̈ʒu���������A
    // ���������ʒu���當����Ō�܂ł�؂�o���ĕԂ��B

    std::string result("");
    std::string::size_type foundIdx = str.find_first_not_of(" \f\n\r\t\v");
    if ( foundIdx != std::string::npos )
    {
        result = str.substr( foundIdx, std::string::npos );  // �������ʒu����Ō�܂�
    }
    return result;
}

/*!
  @brief  �����̋󔒗ޕ�����S�Ď�菜��
  @param  [in]  str  ������
  @return �����̋󔒗ޕ�����S�Ď�菜����������
  @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u
*/
std::string rtrim( const std::string& str )
{
    // �󔒗ޕ����ł͂Ȃ��Ō�̈ʒu���������A
    // �ꕶ���ڂ��猩�������ʒu�܂ł̕������؂�o���B

    std::string result("");
    std::string::size_type foundIdx = str.find_last_not_of(" \f\n\r\t\v");
    if ( foundIdx != std::string::npos )
    {
        result = str.substr( 0, foundIdx + 1 );  // ���������ʒu�܂ł̕������؂肾��
    }
    return result;
}

} // namespace izm
