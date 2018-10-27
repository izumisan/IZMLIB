#ifndef IZM_LITERALS_LENGTHLITERALS_H
#define IZM_LITERALS_LENGTHLITERALS_H

namespace izm
{
namespace literals
{

/*!
  @brief  _kmリテラル
  @example 1.0_km -> 1000.0 [m]
*/
constexpr double operator""_km( const long double km )
{
    return km * 1000.0;
}

/*!
  @brief  _mリテラル
  @example 1.0_m -> 1.0 [m]
*/
constexpr double operator""_m( const long double m )
{
    return m;
}

/*!
  @brief  _cmリテラル
  @example 100.0_cm -> 1.0 [m]
*/
constexpr double operator""_cm( const long double cm )
{
    return cm * 0.01;
}

/*!
  @brief  _mmリテラル
  @example 1000.0_mm -> 1.0 [m]
*/
constexpr double operator""_mm( const long double mm )
{
    return mm * 0.001;
}

} // namespace literals
} // namespace izm

#if !defined(NO_USING_IZM_LITERALS)
using namespace izm::literals;
#endif

#endif // IZM_LITERALS_LENGTHLITERALS_H
