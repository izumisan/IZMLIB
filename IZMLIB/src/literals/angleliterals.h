#ifndef IZM_LITERALS_ANGLELITERALS_H
#define IZM_LITERALS_ANGLELITERALS_H

//#include <cmath>

namespace izm
{
namespace literals
{

/*!
  @brief  _degリテラル
  @example 360.0_deg => 2π [rad]
*/
constexpr double operator""_deg ( const long double deg )
{
//    constexpr double pi = 4.0 * std::atan( 1.0 );
//    return deg * pi / 180.0;
    return deg * M_PI / 180.0;
}

/*!
  @brief  _radリテラル
  @example 1.0_rad => 1.0 [rad]
*/
constexpr double operator""_rad ( const long double rad )
{
    return rad;
}

} // namespace literals
} // namespace izm

#endif // IZM_LITERALS_ANGLELITERALS_H
