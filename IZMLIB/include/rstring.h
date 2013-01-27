/*!
  @file  rstring.h
  @brief RStringクラスのヘッダファイル
*/
#ifndef IZM_RSTRING_H
#define IZM_RSTRING_H

#include <string>
#include <vector>

namespace izm
{

class RString : public std::string
{
// コンストラクタ・デストラクタ
public:
    RString();
    explicit RString( const double num );
    RString( const std::string& str );

    virtual ~RString();

// 演算子
public:
    // 代入演算子
    RString& operator =( const std::string& rhs );
    RString& operator =( const RString& rhs );

    // 加算演算子
    RString operator +( const double rhs );

// 操作
public:
    // 型変換
    int to_i() const;
    int toInt() const;
    double to_f() const;
    double toDouble() const;
    std::string to_s() const;
    std::string toStdString() const;

    // アクセス
    char first() const;
    char last() const;

    // 判定
    bool include( const std::string& str ) const;

    // 分割
    std::vector<RString> split( const std::string& delimiter = " " ) const;

    // 改行コードの削除
    RString  chomp() const;
    RString& chomp_d();     // 破壊メソッド

    // 末尾文字の削除
    RString  chop() const;
    RString& chop_d();      // 破壊メソッド

    // 空白類文字の削除
    RString  strip() const;
    RString& strip_d();     // 破壊メソッド

    RString  lstrip() const;
    RString& lstrip_d();    // 破壊メソッド

    RString  rstrip() const;
    RString& rstrip_d();    // 破壊メソッド

    // strip, lstrip, rstripの別名メソッド
    RString  trim() const;
    RString& trim_d();      // 破壊メソッド

    RString  ltrim() const;
    RString& ltrim_d();     // 破壊メソッド

    RString  rtrim() const;
    RString& rtrim_d();     // 破壊メソッド

    // 文字列の削除
    RString  remove( const std::string& str ) const;
    RString& remove_d( const std::string& str );     // 破壊メソッド

    // 文字列の置換
    RString  sub( const std::string& before, const std::string& after ) const;
    RString& sub_d( const std::string& before, const std::string& after );      // 破壊メソッド

    RString  gsub( const std::string& before, const std::string& after ) const;
    RString& gsub_d( const std::string& before, const std::string& after );     // 破壊メソッド

    // 大文字 <=> 小文字
    RString  upcase() const;
    RString& upcase_d();        // 破壊メソッド

    RString  downcase() const;
    RString& downcase_d();      // 破壊メソッド
};

} // namcespace izm

#endif // IZM_RSTRING_H
