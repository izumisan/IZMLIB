/*!
  @file  util.cpp
  @brief utilモジュールの実装ファイル
*/
#include <string>
#include <vector>

#include "util.h"

namespace izm
{

/*!
  @brief  文字列をデリミタで分割する。
  @param  [in]  str        分割する文字列
  @param  [in]  delimiter  デリミタ (デフォルト引数=" ")
  @return 分割された文字列のベクタ
  @note   連続するデリミタは一つとみなす\n
          (例) "abacdaaefga"を"a"で分割した場合の戻り値->{"b", "cd", "efg"}
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
        // デリミタが連続している場合
        else
        {
            currentIdx += delimiter.size();
        }
    }
    // 残りの回収
    if ( currentIdx < str.size() )
    {
        result.push_back( str.substr( currentIdx, std::string::npos ) );
    }
    return result;
}

/*!
  @brief  前後の空白類文字を全て取り除く
  @param  [in]  str  文字列
  @return 前後の空白類文字を全て取り除いた文字列
  @note   空白類文字: 空白、書式送り、改行、復帰、水平タブ、垂直タブ
*/
std::string trim( const std::string& str )
{
    std::string result( str );
    result = ltrim( result );
    result = rtrim( result );
    return result;
}

/*!
  @brief  先頭の空白類文字を全て取り除く
  @param  [in]  str  文字列
  @return 先頭の空白類文字を全て取り除いた文字列
  @note   空白類文字: 空白、書式送り、改行、復帰、水平タブ、垂直タブ
*/
std::string ltrim( const std::string& str )
{
    // 空白類文字ではない最初の位置を検索し、
    // 見つかった位置から文字列最後までを切り出して返す。

    std::string result("");
    std::string::size_type foundIdx = str.find_first_not_of(" \f\n\r\t\v");
    if ( foundIdx != std::string::npos )
    {
        result = str.substr( foundIdx, std::string::npos );  // 見つけた位置から最後まで
    }
    return result;
}

/*!
  @brief  末尾の空白類文字を全て取り除く
  @param  [in]  str  文字列
  @return 末尾の空白類文字を全て取り除いた文字列
  @note   空白類文字: 空白、書式送り、改行、復帰、水平タブ、垂直タブ
*/
std::string rtrim( const std::string& str )
{
    // 空白類文字ではない最後の位置を検索し、
    // 一文字目から見つかった位置までの文字列を切り出す。

    std::string result("");
    std::string::size_type foundIdx = str.find_last_not_of(" \f\n\r\t\v");
    if ( foundIdx != std::string::npos )
    {
        result = str.substr( 0, foundIdx + 1 );  // 見つかった位置までの文字列を切りだす
    }
    return result;
}

} // namespace izm
