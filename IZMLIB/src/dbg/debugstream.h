/*!
  @file  debugstream.h
*/
#ifndef IZM_DBG_DEBUGSTREAM_H
#define IZM_DBG_DEBUGSTREAM_H

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
class DebugStream
{
public:
    DebugStream()
        : DebugStream( "izm.debug.log" )
    {
    }

    DebugStream( const std::string& path )
        : m_path( path )
        , m_ofs( path )
    {
    }

    virtual ~DebugStream()
    {
        m_ofs.flush();
        m_ofs.close();
    }

public:
    DebugStream& operator << ( const int value ) { return operator << ( std::to_string( value ) ); }
    DebugStream& operator << ( const double value ) { return operator << ( std::to_string( value ) ); }
    DebugStream& operator << ( const char* str ) { return operator << ( std::string( str ) ); }
    DebugStream& operator << ( const std::string& str )
    {
        if ( isTiming() )
        {
            std::cout << str << " ";
            m_ofs << str << " ";
        }
        return *this;
    }

    /*!
      @brief  マニピュレータを受け取る挿入演算子
      @param  [in]  manip  DebugStreamを引数にとり、DebugStreamを返す関数ポインタ
    */
    DebugStream& operator << ( DebugStream& ( *manip )( DebugStream& ) )
    {
        return ( *manip )( *this );
    }

public:
    /*!
    */
    std::string path() const
    {
        return m_path;
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
    DebugStream& eol()
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
    std::string m_path;
    std::ofstream m_ofs;
    unsigned long long m_eolCount = 0uLL;
    int m_onceEveryX = 1;
    unsigned long long m_baseCount = 0uLL;
};

} // namespace dbg
} // namespace izm

// マニピュレータ（DebugStreamとセットで使うので、インクルードしておく）
#include "dsmanipulator.h"

#endif // IZM_DBG_DEBUGSTREAM_H
