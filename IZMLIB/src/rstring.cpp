/*!
  @file  rstring.cpp
  @brief RString�N���X�̎����t�@�C��
*/
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "rstring.h"

namespace izm
{

//==============================================================================
//! @brief  �R���X�g���N�^
//==============================================================================
RString::RString()
    : std::string()
{}

//==============================================================================
//! @brief  �R���X�g���N�^
//==============================================================================
RString::RString( const double num )
    : std::string()
{
    std::stringstream ss;
    ss << num;
    *this = ss.str();
}

//==============================================================================
//! @brief  �R���X�g���N�^
//==============================================================================
RString::RString( const std::string& str )
    : std::string( str )
{}

//==============================================================================
//! @brief  �f�X�g���N�^
//==============================================================================
RString::~RString()
{}

//==============================================================================
//! @brief  ������Z�q
//==============================================================================
RString& RString::operator =( const std::string& rhs )
{
    std::string::operator =( rhs );
    return *this;
}

//==============================================================================
//! @brief  ������Z�q
//==============================================================================
RString& RString::operator =( const RString& rhs )
{
    if ( this != &rhs )
    {
        std::string::operator =( rhs );
    }
    return *this;
}

//==============================================================================
//! @brief  ���Z���Z�q
//==============================================================================
RString RString::operator +( const double rhs )
{
    RString result("");
    std::stringstream ss;
    ss << *this << rhs;
    result = ss.str();
    return result;
}

//==============================================================================
//! @brief  int�^�ւ̕ϊ�
//==============================================================================
int RString::to_i() const
{
    return atoi( this->c_str() );
}

//==============================================================================
//! @brief  int�^�ւ̕ϊ�
//! @note   to_i()�̕ʖ�
//==============================================================================
int RString::toInt() const
{
    return this->to_i();
}

//==============================================================================
//! @brief  double�^�ւ̕ϊ�
//==============================================================================
double RString::to_f() const
{
    return atof( this->c_str() );
}

//==============================================================================
//! @brief  double�^�ւ̕ϊ�
//! @note   to_f()�̕ʖ�
//==============================================================================
double RString::toDouble() const
{
    return this->to_f();
}

//==============================================================================
//! @brief  std::string�^�ւ̕ϊ�
//==============================================================================
std::string RString::to_s() const
{
    return static_cast<std::string>(*this);  // �A�b�v�L���X�g
}

//==============================================================================
//! @brief  std::string�^�ւ̕ϊ�
//! @note   to_s()�̕ʖ�
//==============================================================================
std::string RString::toStdString() const
{
    return this->to_s();
}

//==============================================================================
//! @brief  �擪������Ԃ�
//==============================================================================
char RString::first() const
{
    char result = '\0';
    if( this->empty() != true )
    {
        result = this->at(0);
    }
    return result;
}

//==============================================================================
//! @brief  ����������Ԃ�
//==============================================================================
char RString::last() const
{
    char result = '\0';
    if( this->empty() != true )
    {
        result = this->at( this->size() - 1 );
    }
    return result;
}

//==============================================================================
//! @brief  �����񂪊܂܂�Ă��邩�ۂ��𔻒肷��
//==============================================================================
bool RString::include( const std::string& str ) const
{
    bool result = false;
    const std::string::size_type foundIdx = this->find( str );
    if ( foundIdx != std::string::npos )
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

//==============================================================================
//! @brief  ��������ꕶ���Â�������B
//! @return �������ꂽ������̃x�N�^
//==============================================================================
std::vector<std::string> RString::split() const
{
    std::vector<std::string> result;
    for ( std::string::const_iterator it = this->begin(); it != this->end(); ++it )
    {
        result.push_back( &( *it ) );
    }
    return result;
}

//==============================================================================
//! @brief  �f���~�^�ŕ��������������Ԃ�
//! @param  [in]  delimiter  �f���~�^
//! @return �������ꂽ������̃x�N�^
//! @note   �A������f���~�^�͈�Ƃ݂Ȃ�\n
//!         (��) "abacdaaefga"��"a"�ŕ��������ꍇ�̖߂�l->{"b", "cd", "efg"}
//==============================================================================
std::vector<std::string> RString::split( const std::string& delimiter ) const
{
    std::vector<std::string> result;
    if ( delimiter.empty() != true )
    {
        std::string::size_type currentIdx = 0;
        std::string::size_type foundIdx = 0;

        while( ( foundIdx = this->find( delimiter, currentIdx ) ) != std::string::npos )
        {
            if ( foundIdx != currentIdx )
            {
                result.push_back( substr( currentIdx, foundIdx - currentIdx ) );
                currentIdx = foundIdx + delimiter.size();
            }
            // �f���~�^���A�����Ă���ꍇ
            else
            {
                currentIdx += delimiter.size();
            }
        }
        // �c��̉��
        if ( currentIdx <= this->size() - 1 )
        {
            result.push_back( substr( currentIdx, std::string::npos ) );
        }
    }
    else
    {
        result = this->split();
    }
    return result;
}

//==============================================================================
//! @brief  �����̉��s�R�[�h����菜��
//! @return ���s�R�[�h����菜����������
//==============================================================================
RString RString::chomp() const
{
    RString result(*this);
    // ����������LF�̏ꍇ�͍폜����
    if( result.last() == '\n' )
    {
        result = result.erase( result.size() - 1 );
    }
    // ����������CR�̏ꍇ�͍폜����
    if( result.last() == '\r' )
    {
        result = result.erase( result.size() - 1 );
    }
    return result;
}

//==============================================================================
//! @brief  �����̉��s�R�[�h����菜��
//! @return ���s�R�[�h����菜����������
//! @note   chomp()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::chomp_d()
{
    *this = this->chomp();
    return *this;
}

//==============================================================================
//! @brief  �����̈ꕶ������菜��
//! @return �����̈ꕶ������菜����������
//==============================================================================
RString RString::chop() const
{
    RString result(*this);
    if( !( result.empty() ) )
    {
        result = result.erase( result.size() - 1 );
    }
    return result;
}

//==============================================================================
//! @brief  �����̈ꕶ������菜��
//! @return �����̈ꕶ������菜����������
//! @note   chop()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::chop_d()
{
    *this = this->chop();
    return *this;
}


//==============================================================================
//! @brief  �O��̋󔒗ޕ�����S�Ď�菜��
//! @return �O��̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u
//==============================================================================
RString RString::strip() const
{
    RString result("");
    result = result.lstrip();
    result = result.rstrip();
    return result;
}

//==============================================================================
//! @brief  �O��̋󔒗ޕ�����S�Ď�菜��
//! @return �O��̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         strip()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::strip_d()
{
    *this = this->strip();
    return *this;
}

//==============================================================================
//! @brief  �擪�̋󔒗ޕ�����S�Ď�菜��
//! @return �擪�̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u
//==============================================================================
RString RString::lstrip() const
{
    RString result("");
    std::string::size_type foundIdx = this->find_first_not_of(" \f\n\r\t\v");
    if ( foundIdx != std::string::npos )
    {
        result = this->substr( foundIdx, std::string::npos );
    }
    return result;
}

//==============================================================================
//! @brief  �擪�̋󔒗ޕ�����S�Ď�菜��
//! @return �擪�̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         lstrip()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::lstrip_d()
{
    *this = this->lstrip();
    return *this;
}

//==============================================================================
//! @brief  �����̋󔒗ޕ�����S�Ď�菜��
//! @return �����̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u
//==============================================================================
RString RString::rstrip() const
{
    RString result("");
    std::string::size_type foundIdx = this->find_last_not_of(" \f\n\r\t\v");
    if ( foundIdx != std::string::npos )
    {
        result = this->substr( 0, foundIdx + 1 );
    }
    return result;
}

//==============================================================================
//! @brief  �����̋󔒗ޕ�����S�Ď�菜��
//! @return �����̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         rstrip()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::rstrip_d()
{
    *this = this->rstrip();
    return *this;
}

//==============================================================================
//! @brief  �O��̋󔒗ޕ�����S�Ď�菜��
//! @return �O��̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         strip()�̕ʖ�
//==============================================================================
RString RString::trim() const
{
    return this->strip();
}

//==============================================================================
//! @brief  �O��̋󔒗ޕ�����S�Ď�菜��
//! @return �O��̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         strip()�̕ʖ�\n
//!         �j�󃁃\�b�h
//==============================================================================
RString& RString::trim_d()
{
    return this->strip_d();
}

//==============================================================================
//! @brief  �擪�̋󔒗ޕ�����S�Ď�菜��
//! @return �擪�̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         lstrip()�̕ʖ�
//==============================================================================
RString RString::ltrim() const
{
    return this->lstrip();
}

//==============================================================================
//! @brief  �擪�̋󔒗ޕ�����S�Ď�菜��
//! @return �擪�̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         lstrip_d()�̕ʖ�\n
//!         �j�󃁃\�b�h
//==============================================================================
RString& RString::ltrim_d()
{
    return this->lstrip_d();
}

//==============================================================================
//! @brief  �����̋󔒗ޕ�����S�Ď�菜��
//! @return �����̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         rstrip()�̕ʖ�
//==============================================================================
RString RString::rtrim() const
{
    return this->rstrip();
}

//==============================================================================
//! @brief  �����̋󔒗ޕ�����S�Ď�菜��
//! @return �����̋󔒗ޕ�����S�Ď�菜����������
//! @note   �󔒗ޕ���: �󔒁A��������A���s�A���A�A�����^�u�A�����^�u\n
//!         rstrip_d()�̕ʖ�\n
//!         �j�󃁃\�b�h
//==============================================================================
RString& RString::rtrim_d()
{
    return this->rstrip_d();
}

//==============================================================================
//! @brief  ��������폜����
//! @param  [in]  str  �폜���镶����
//! @return �����Ŏw�肵����������폜����������
//==============================================================================
RString RString::remove( const std::string& str ) const
{
    RString result(*this);
    if ( str.empty() != true )
    {
        std::string::size_type foundIdx = 0;
        while( ( foundIdx = result.find( str ) ) != std::string::npos )
        {
            result = result.erase( foundIdx, str.size() );
        }
    }
    return result;
}

//==============================================================================
//! @brief  ��������폜����
//! @param  [in]  str  �폜���镶����
//! @return �����Ŏw�肵����������폜����������
//! @note   deletePartOf()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::remove_d( const std::string& str )
{
    *this = this->remove( str );
    return *this;
}

//==============================================================================
//! @brief  �������u������
//! @param  [in]   before  �ϊ��O�̕�����
//! @param  [out]  after   �ϊ���̕�����
//! @return �u����̕�����
//==============================================================================
RString RString::sub( const std::string& before, const std::string& after ) const
{
    RString result(*this);
    if ( before.empty() != true )
    {
        std::string::size_type foundIdx = 0;
        if( ( foundIdx = result.find_first_of( before ) ) != std::string::npos )
        {
            result = result.replace( foundIdx, before.size(), after );
        }
    }
    return result;
}

//==============================================================================
//! @brief  �������u������
//! @param  [in]   before  �ϊ��O�̕�����
//! @param  [out]  after   �ϊ���̕�����
//! @return �u����̕�����
//! @note   sub()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::sub_d( const std::string& before, const std::string& after )
{
    *this = this->sub( before, after );
    return *this;
}

//==============================================================================
//! @brief  ��������ċA�I�ɒu������
//! @param  [in]   before  �ϊ��O�̕�����
//! @param  [out]  after   �ϊ���̕�����
//! @return �u����̕�����
//==============================================================================
RString RString::gsub( const std::string& before, const std::string& after ) const
{
    RString result;
    if ( before.empty() != true )
    {
        std::string::size_type currentIdx = 0;
        std::string::size_type foundIdx = 0;
        while ( ( foundIdx = this->find( before, currentIdx ) ) != std::string::npos )
        {
            result += this->substr( currentIdx, foundIdx - currentIdx );
            result += after;
            currentIdx = foundIdx + before.size();
        }
        if ( currentIdx < this->size() )
        {
            result += this->substr( currentIdx, std::string::npos );
        }
    }
    else
    {
        result = *this;
    }
    return result;
}

//==============================================================================
//! @brief  ��������ċA�I�ɒu������
//! @param  [in]   before  �ϊ��O�̕�����
//! @param  [out]  after   �ϊ���̕�����
//! @return �u����̕�����
//! @note   gsub()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::gsub_d( const std::string& before, const std::string& after )
{
    *this = this->gsub( before, after );
    return *this;
}

//==============================================================================
//! @brief  �啶���ɕϊ�����
//! @return �啶���ɕϊ�����������
//==============================================================================
RString RString::upcase() const
{
    RString result(*this);
    //std::transform( this->begin(), this->end(), result.begin(), std::toupper );
    std::transform( this->begin(), this->end(), result.begin(), static_cast<int (*)(int)>( std::toupper ) );
    return result;
}

//==============================================================================
//! @brief  �啶���ɕϊ�����
//! @return �啶���ɕϊ�����������
//! @note   upcase()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::upcase_d()
{
    *this = this->upcase();
    return *this;
}

//==============================================================================
//! @brief  �������ɕϊ�����
//! @return �������ɕϊ�����������
//==============================================================================
RString RString::downcase() const
{
    RString result(*this);
    //std::transform( this->begin(), this->end(), result.begin(), std::tolower );
    std::transform( this->begin(), this->end(), result.begin(), static_cast<int (*)(int)>( std::tolower ) );
    return result;
}

//==============================================================================
//! @brief  �������ɕϊ�����
//! @return �������ɕϊ�����������
//! @note   downcase()�̔j�󃁃\�b�h��
//==============================================================================
RString& RString::downcase_d()
{
    *this = this->downcase();
    return *this;
}

} // namespace izm
