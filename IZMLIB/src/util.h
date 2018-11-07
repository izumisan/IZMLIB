/*!
  @file  util.h
  @brief utilモジュールのヘッダファイル
*/
#ifndef IZM_UTIL_H
#define IZM_UTIL_H

#include <string>
#include <vector>

namespace izm
{

std::vector<std::string> split( const std::string& str, const std::string& delimiter = " " );
std::string replace( const std::string& str, const std::string& before, const std::string& after );

std::string trim( const std::string& str );
std::string ltrim( const std::string& str );
std::string rtrim( const std::string& str );

} // namespace izm

#endif // IZM_UTIL_H
