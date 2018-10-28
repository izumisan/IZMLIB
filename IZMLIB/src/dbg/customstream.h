/*!
  @file  customstream.h
*/
#ifndef IZM_DBG_CUSTOMSTREAM_H
#define IZM_DBG_CUSTOMSTREAM_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

namespace izm
{
namespace dbg
{

/*!
  @class  標準出力とファイルの両方に出力するストリーム
*/
class CustomStream
{
public:
    CustomStream()
    {
    }

    CustomStream( const std::string& path )
        : m_ofs( path )
    {
    }

    virtual ~CustomStream()
    {
    }

public:
    CustomStream& operator << ( const int value )
    {
        return operator << ( std::to_string( value ) );
    }
    CustomStream& operator << ( const double value )
    {
        return operator << ( std::to_string( value ) );
    }
    CustomStream& operator << ( const std::string& str )
    {
        if ( isTiming() )
        {
            std::cout << str;
            m_ofs << str;
        }
        return *this;
    }

    /*!
      @brief  マニピュレータを受け取る挿入演算子
      @param  [in]  manip  CustomStreamを引数にとり、CustomStreamを返す関数ポインタ
    */
    CustomStream& operator << ( CustomStream& ( *manip )( CustomStream& ) )
    {
        return ( *manip )( *this );
    }

    /*!
    */
    void setOnceEvery( const int x )
    {
        m_onceEveryX = (std::max)( 1, x );  // maxマクロの展開抑制のため、()で囲む
        m_baseCount = m_eolCount;
    }

    /*!
      @brief  改行コードを出力する
    */
    CustomStream& eol()
    {
        if ( isTiming() )
        {
            std::cout << std::endl;
            m_ofs << std::endl;
        }
        ++m_eolCount;
        return *this;
    }

    /*!
      @brief  バッファをフラッシュする
    */
    void flush()
    {
        m_ofs.flush();
    }

private:
    bool isTiming() const
    {
        return ( ( m_eolCount - m_baseCount ) % m_onceEveryX == 0 );
    }

private:
    std::ofstream m_ofs = std::ofstream("izm.debug.log");
    unsigned long long m_eolCount = 0uLL:
    int m_onceEveryX = 1;
    unsigned long long m_baseCount = 0uLL;
};

} // namespace dbg
} // namespace izm

// マニピュレータ
#include "csmanipulator.h"

#endif // IZM_DBG_CUSTOMSTREAM_H

