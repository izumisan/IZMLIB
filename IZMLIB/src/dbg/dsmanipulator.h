/*!
  @file  csmanipulator.h
*/
#ifndef IZM_DBG_CSMANIPULATOR_H
#define IZM_DBG_CSMANIPULATOR_H

#include <ctime>
#include <cstdarg>
#include <cstring>
#include <string>
#include "customstream.h"

// cs << izm::dbg::callerInfo( __FILE__, __LINE__, __func__ ) を
// cs << CALLERINFO と省略するためのマクロ定義
#define CALLERINFO ( izm::dbg::callerInfo( __FILE__, __LINE__, __func__, true ) )
#define CALLERINFO_L ( izm::dbg::callerInfo( __FILE__, __LINE__,__func__, false ) )

namespace izm
{
namespace dbg
{

////////////////////////////////////////////////////////////////////////////////
/*!
  @brief  endlマニピュレーター
*/
CustomStream& endl( CustomStream& cs )
{
    cs.eol();
    cs.flush();
    return cs;
}
////////////////////////////////////////////////////////////////////////////////
/*!
  @brief  timestampマニピュレーター
*/
CustomStream& timestamp( CustomStream& cs )
{
    time_t t = time( nullptr );
    const tm* now = localtime( &t );
    char buff[] = "YYYY-MM-DD hh:mm:ss";
    strftime( buff, sizeof( buff ), "%Y-%m-%d %H:%M:%S", now );
    return cs << buff;
}
////////////////////////////////////////////////////////////////////////////////
/*!
  @class  callerInfoマニピュレーター
*/
class callerInfo
{
    friend CustomStream& operator << ( CustomStream& cs, callerInfo manip );

public:
    callerInfo( const std::string& fileName,
                const long lineNumber,
                const std::string& funcName,
                bool excludeDirectoryName = true )
        : m_fileName( fileName )
        , m_lineNumber( lineNumber )
        , m_funcName( funcName )
    {
        if ( excludeDirectoryName )
        {
            // ファイル名を抽出する
            const auto&& lastDelimiter = m_fileName.find_last_of( "/\\" );
            if ( lastDelimiter != std::string::npos )
            {
                const auto&& startIndex = lastDelimiter + 1;
                if ( startIndex < m_fileName.size() )
                {
                    m_fileName = m_fileName.substr( startIndex );
                }
            }
        }
    }

private:
    CustomStream& operator ()( CustomStream& cs )
    {
        return cs << printf( "%s(%d) %s:", m_fileName.c_str(), m_lineNumber, m_funcName.c_str() );
    }

private:
    std::string m_fileName;
    long m_lineNumber;
    std::string m_funcName;
};

/*!
  @brief  callerInfoクラスを引数に取るCustomStreamの挿入演算子のオーバーロード
*/
CustomStream& operator << ( CustomStream& cs, callerInfo manip )
{
    return manip( cs );
}
////////////////////////////////////////////////////////////////////////////////
/*!
  @class printfマニピュレーター
*/
class printf
{
    friend CustomStream& operator << ( CustomStream& cs, printf manip );

public:
    printf( const char* format, ... )
        : m_buff()
    {
        char buff[1024] = {};
        memset( buff, 0x00, sizeof( buff ) );

        va_list valist;
        va_start( valist, format );
        vsnprintf( buff, sizeof( buff ), format, valist );
        va_end( valist );

        m_buff = std::string( buff );
    }
private:
    CustomStream& operator ()( CustomStream& cs )
    {
        return cs << m_buff;
    }
private:
    std::string m_buff;
};

/*!
  @brief  printfクラスを引数にとるCustomStreamの挿入演算子のオーバーロード
*/
CustomStream& operator << ( CustomStream& cs, printf manip )
{
    return manip( cs );
}
////////////////////////////////////////////////////////////////////////////////
/*!
  @class everyマニピュレーター
*/
class every
{
    friend CustomStream& operator << ( CustomStream& cs, every manip );

public:
    every( const int onceEveryX )
        : m_value( onceEveryX )
    {
    }
private:
    CustomStream& operator ()( CustomStream& cs )
    {
        cs.setOnceEvery( m_value );
        return cs;
    }
private:
    int m_value;
};

/*!
  @brief  everyクラスを引数にとるCustomStreamの挿入演算子のオーバーロード
*/
CustomStream& operator << ( CustomStream& cs, every manip )
{
    return manip( cs );
}

} // namespace dbg
} // namespace izm

#endif // IZM_CSMANIPULATOR_H
