/*!
  @file  rstring.h
  @brief RStringNXΜwb_t@C
*/
#ifndef IZM_RSTRING_H
#define IZM_RSTRING_H

#include <string>
#include <vector>

namespace izm
{

class RString : public std::string
{
// RXgN^EfXgN^
public:
    RString();
    explicit RString( const double num );
    RString( const std::string& str );

    ~RString();

// Zq
public:
    // γόZq
    RString& operator =( const std::string& rhs );
    RString& operator =( const RString& rhs );

    // ΑZZq
    RString operator +( const double rhs );

// μ
public:
    // ^Ο·
    int to_i() const;
    int toInt() const;
    double to_f() const;
    double toDouble() const;
    std::string to_s() const;
    std::string toStdString() const;

    // ANZX
    char first() const;
    char last() const;

    // »θ
    bool include( const std::string& str ) const;

    // ͺ
    std::vector<std::string> split() const;
    std::vector<std::string> split( const std::string& delimiter ) const;

    // όsR[hΜν
    RString  chomp() const;
    RString& chomp_d();     // jσ\bh

    // φΆΜν
    RString  chop() const;
    RString& chop_d();      // jσ\bh

    // σήΆΜν
    RString  strip() const;
    RString& strip_d();     // jσ\bh

    RString  lstrip() const;
    RString& lstrip_d();    // jσ\bh

    RString  rstrip() const;
    RString& rstrip_d();    // jσ\bh

    RString  trim() const;
    RString& trim_d();      // jσ\bh

    RString  ltrim() const;
    RString& ltrim_d();     // jσ\bh

    RString  rtrim() const;
    RString& rtrim_d();     // jσ\bh

    // ΆρΜν
    RString  remove( const std::string& str ) const;
    RString& remove_d( const std::string& str );     // jσ\bh

    // ΆρΜu·
    RString  sub( const std::string& before, const std::string& after ) const;
    RString& sub_d( const std::string& before, const std::string& after );      // jσ\bh

    RString  gsub( const std::string& before, const std::string& after ) const;
    RString& gsub_d( const std::string& before, const std::string& after );     // jσ\bh

    // εΆ <=> ¬Ά
    RString  upcase() const;
    RString& upcase_d();        // jσ\bh

    RString  downcase() const;
    RString& downcase_d();      // jσ\bh
};

} // namcespace izm

#endif // IZM_RSTRING_H
