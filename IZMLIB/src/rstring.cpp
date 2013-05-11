/*!
  @file  rstring.cpp
  @brief RStringクラスの実装ファイル
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

/*!
  @brief  コンストラクタ
*/
RString::RString()
    : std::string()
{}

/*!
  @brief  コンストラクタ
*/
RString::RString( const double num )
    : std::string()
{
    std::stringstream ss;
    ss << num;
    *this = ss.str();
}

/*!
  @brief  コンストラクタ
*/
RString::RString( const std::string& str )
    : std::string( str )
{}

/*!
  @brief  デストラクタ
*/
RString::~RString()
{}

/*!
  @brief  代入演算子
*/
RString& RString::operator =( const std::string& rhs )
{
    std::string::operator =( rhs );
    return *this;
}

/*!
  @brief  代入演算子
*/
RString& RString::operator =( const RString& rhs )
{
    if ( this != &rhs )
    {
        std::string::operator =( rhs.to_s() );
    }
    return *this;
}

/*!
  @brief  加算演算子
*/
RString RString::operator +( const double rhs )
{
    RString result("");
    std::stringstream ss;
    ss << *this << rhs;
    result = ss.str();
    return result;
}

/*!
  @brief  int型への変換
*/
int RString::to_i() const
{
    return atoi( this->c_str() );
}

/*!
  @brief  to_i()の別名メソッド
*/
int RString::toInt() const
{
    return this->to_i();
}

/*!
  @brief  double型への変換
*/
double RString::to_f() const
{
    return atof( this->c_str() );
}

/*!
  @brief  to_f()の別名メソッド
*/
double RString::toDouble() const
{
    return this->to_f();
}

/*!
  @brief  std::string型への変換
*/
std::string RString::to_s() const
{
    return static_cast<std::string>(*this);  // アップキャスト
}

/*!
  @brief  to_s()の別名メソッド
*/
std::string RString::toStdString() const
{
    return this->to_s();
}

/*!
  @brief  先頭文字を返す
*/
char RString::first() const
{
    char result = '\0';
    if( this->empty() != true )
    {
        result = this->at(0);
    }
    return result;
}

/*!
  @brief  末尾文字を返す
*/
char RString::last() const
{
    char result = '\0';
    if( this->empty() != true )
    {
        result = this->at( this->size() - 1 );
    }
    return result;
}

/*!
  @brief  first()の別名メソッド
*/
char RString::head() const
{
    return this->first();
}

/*!
  @brief  last()の別名メソッド
*/
char RString::tail() const
{
    return this->last();
}

/*!
  @brief  文字列が含まれているか否かを判定する
*/
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

/*!
  @brief  デリミタで分割した文字列を返す
  @param  [in]  delimiter  デリミタ (デフォルト引数=" ")
  @return 分割された文字列のベクタ
  @note   連続するデリミタは一つとみなす\n
          (例) "abacdaaefga"を"a"で分割した場合の戻り値->{"b", "cd", "efg"}
*/
std::vector<RString> RString::split( const std::string& delimiter ) const
{
    std::vector<RString> result;
    std::string::size_type currentIdx = 0;
    std::string::size_type foundIdx = 0;

    while( ( foundIdx = this->find( delimiter, currentIdx ) ) != std::string::npos )
    {
        if ( foundIdx != currentIdx )
        {
            result.push_back( substr( currentIdx, foundIdx - currentIdx ) );
            currentIdx = foundIdx + delimiter.size();
        }
        // デリミタが連続している場合
        else
        {
            currentIdx += delimiter.size();
        }
    }
    // 残りの回収
    if ( currentIdx <= this->size() - 1 )
    {
        result.push_back( substr( currentIdx, std::string::npos ) );
    }

    return result;
}

/*!
  @brief  デリミタの左部分を返す(最短一致検索)
  @param  [in]  delimiter  デリミタ (デフォルト引数=" ")
  @return デリミタの左部分
*/
RString RString::leftPart( const std::string& delimiter ) const
{
    RString result;
    std::string::size_type foundIdx = this->find( delimiter );
    if ( ( delimiter.size() != 0 ) && ( foundIdx != std::string::npos ) )
    {
        result = this->substr( 0, foundIdx );
    }
    return result;
}

/*!
  @brief  leftPart()の破壊メソッド版
*/
RString& RString::leftPart_d( const std::string& delimiter )
{
    *this = this->leftPart( delimiter );
    return *this;
}

/*!
  @brief  デリミタの左部分を返す(最長一致検索)
  @param  [in]  delimiter  デリミタ (デフォルト引数=" ")
  @return デリミタの左部分
*/
RString RString::leftPartR( const std::string& delimiter ) const
{
    return this->reverse().rightPart( RString(delimiter).reverse() ).reverse();
}

/*!
  @brief  leftPartR()の破壊メソッド版
*/
RString& RString::leftPartR_d( const std::string& delimiter )
{
    *this = this->leftPartR( delimiter );
    return *this;
}

/*!
  @brief  デリミタの右部分を返す(最短一致検索)
  @param  [in]  delimiter  デリミタ (デフォルト引数=" ")
  @return デリミタの右部分
*/
RString RString::rightPart( const std::string& delimiter ) const
{
    RString result;
    std::string::size_type foundIdx = this->find( delimiter );
    if ( ( delimiter.size() != 0 ) && ( foundIdx != std::string::npos ) )
    {
        std::string::size_type startIdx = foundIdx + delimiter.size();
        if ( startIdx < this->size() )
        {
            result = this->substr( startIdx, std::string::npos );
        }
        else
        {
            result = "";
        }
    }
    return result;
}

/*!
  @brief  rightPart()の破壊メソッド版
*/
RString& RString::rightPart_d( const std::string& delimiter )
{
    *this = this->rightPart( delimiter );
    return *this;
}

/*!
  @brief  デリミタの右部分を返す(最長一致検索)
  @param  [in]  delimiter  デリミタ (デフォルト引数=" ")
  @return デリミタの右部分
*/
RString RString::rightPartR( const std::string& delimiter ) const
{
    return this->reverse().leftPart( RString(delimiter).reverse() ).reverse();
}

/*!
  @brief  rightPartR()の破壊メソッド版
*/
RString& RString::rightPartR_d( const std::string& delimiter )
{
    *this = this->rightPartR( delimiter );
    return *this;
}

/*!
  @brief  末尾の改行コードを取り除く
  @return 改行コードを取り除いた文字列
*/
RString RString::chomp() const
{
    RString result(*this);
    // 末尾文字がLFの場合は削除する
    if( result.last() == '\n' )
    {
        result = result.erase( result.size() - 1 );
    }
    // 末尾文字がCRの場合は削除する
    if( result.last() == '\r' )
    {
        result = result.erase( result.size() - 1 );
    }
    return result;
}

/*!
  @brief  chomp()の破壊メソッド版
*/
RString& RString::chomp_d()
{
    *this = this->chomp();
    return *this;
}

/*!
  @brief  末尾の一文字を取り除く
  @return 末尾の一文字を取り除いた文字列
*/
RString RString::chop() const
{
    RString result(*this);
    if( !( result.empty() ) )
    {
        result = result.erase( result.size() - 1 );
    }
    return result;
}

/*!
  @brief  chop()の破壊メソッド版
*/
RString& RString::chop_d()
{
    *this = this->chop();
    return *this;
}

/*!
  @brief  前後の空白類文字を全て取り除く
  @return 前後の空白類文字を全て取り除いた文字列
  @note   空白類文字: 空白、書式送り、改行、復帰、水平タブ、垂直タブ
*/
RString RString::strip() const
{
    RString result("");
    result = result.lstrip();
    result = result.rstrip();
    return result;
}

/*!
  @brief  strip()の破壊メソッド版
*/
RString& RString::strip_d()
{
    *this = this->strip();
    return *this;
}

/*!
  @brief  先頭の空白類文字を全て取り除く
  @return 先頭の空白類文字を全て取り除いた文字列
  @note   空白類文字: 空白、書式送り、改行、復帰、水平タブ、垂直タブ
*/
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

/*!
  @brief  lstrip()の破壊メソッド版
*/
RString& RString::lstrip_d()
{
    *this = this->lstrip();
    return *this;
}

/*!
  @brief  末尾の空白類文字を全て取り除く
  @return 末尾の空白類文字を全て取り除いた文字列
  @note   空白類文字: 空白、書式送り、改行、復帰、水平タブ、垂直タブ
*/
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

/*!
  @brief  rstrip()の破壊メソッド版
*/
RString& RString::rstrip_d()
{
    *this = this->rstrip();
    return *this;
}

/*!
  @brief  strip()の別名メソッド
*/
RString RString::trim() const
{
    return this->strip();
}

/*!
  @brief  strip_d()の別名メソッド
*/
RString& RString::trim_d()
{
    return this->strip_d();
}

/*!
  @brief  lstrip()の別名メソッド
*/
RString RString::ltrim() const
{
    return this->lstrip();
}

/*!
  @brief  lstrip_d()の別名メソッド
*/
RString& RString::ltrim_d()
{
    return this->lstrip_d();
}

/*!
  @brief  rstrip()の別名メソッド
*/
RString RString::rtrim() const
{
    return this->rstrip();
}

/*!
  @brief  rstrip_d()の別名メソッド
*/
RString& RString::rtrim_d()
{
    return this->rstrip_d();
}

/*!
  @brief  文字列を削除する
  @param  [in]  str  削除する文字列
  @return 引数で指定した文字列を削除した文字列
*/
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

/*!
  @brief  remove()の破壊メソッド版
*/
RString& RString::remove_d( const std::string& str )
{
    *this = this->remove( str );
    return *this;
}

/*!
  @brief  文字列を置換する
  @param  [in]   before  変換前の文字列
  @param  [out]  after   変換後の文字列
  @return 置換後の文字列
*/
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

/*!
  @brief  sub()の破壊メソッド版
*/
RString& RString::sub_d( const std::string& before, const std::string& after )
{
    *this = this->sub( before, after );
    return *this;
}

/*!
  @brief  文字列を再帰的に置換する
  @param  [in]   before  変換前の文字列
  @param  [out]  after   変換後の文字列
  @return 置換後の文字列
*/
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

/*!
  @brief  gsub()の破壊メソッド版
*/
RString& RString::gsub_d( const std::string& before, const std::string& after )
{
    *this = this->gsub( before, after );
    return *this;
}

/*!
  @brief  大文字に変換する
  @return 大文字に変換した文字列
*/
RString RString::upcase() const
{
    RString result(*this);
    //std::transform( this->begin(), this->end(), result.begin(), std::toupper );
    std::transform( this->begin(), this->end(), result.begin(), static_cast<int (*)(int)>( std::toupper ) );
    return result;
}

/*!
  @brief  upcase()の破壊メソッド版
*/
RString& RString::upcase_d()
{
    *this = this->upcase();
    return *this;
}

/*!
  @brief  小文字に変換する
  @return 小文字に変換した文字列
*/
RString RString::downcase() const
{
    RString result(*this);
    //std::transform( this->begin(), this->end(), result.begin(), std::tolower );
    std::transform( this->begin(), this->end(), result.begin(), static_cast<int (*)(int)>( std::tolower ) );
    return result;
}

/*!
  @brief  downcase()の破壊メソッド版
*/
RString& RString::downcase_d()
{
    *this = this->downcase();
    return *this;
}

/*!
  @brief  文字列を反転させる
  @return 反転した文字列
*/
RString RString::reverse() const
{
    RString result;
    for ( RString::const_reverse_iterator rit = this->rbegin();
          rit != rend();
          ++rit )
    {
        result += *rit;
    }
    return result;
}

/*!
  @brief  reverse()の破壊メソッド版
*/
RString& RString::reverse_d()
{
    *this = this->reverse();
    return *this;
}

} // namespace izm
