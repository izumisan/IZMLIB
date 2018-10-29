/*!
  @file  dsmanipulator.h
*/
#ifndef IZM_DBG_DSMANIPULATOR_H
#define IZM_DBG_DSMANIPULATOR_H

#include <ctime>
#include <cstdarg>
#include <cstring>
#include <string>
#include "debugstream.h"

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
DebugStream& endl( DebugStream& ds )
{
    ds.eol();
    ds.flush();
    return ds;
}
////////////////////////////////////////////////////////////////////////////////
/*!
  @brief  timestampマニピュレーター
*/
DebugStream& timestamp( DebugStream& ds )
{
    time_t t = time( nullptr );
    const tm* now = localtime( &t );
    char buff[] = "YYYY-MM-DD hh:mm:ss";
    strftime( buff, sizeof( buff ), "%Y-%m-%d %H:%M:%S", now );
    return ds << buff;
}
////////////////////////////////////////////////////////////////////////////////
/*!
  @class printfマニピュレーター
*/
class printf
{
    friend DebugStream& operator << ( DebugStream& ds, printf manip );

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
    DebugStream& operator ()( DebugStream& ds )
    {
        return ds << m_buff;
    }
private:
    std::string m_buff;
};

/*!
  @brief  printfクラスを引数にとるDebugStreamの挿入演算子のオーバーロード
*/
DebugStream& operator << ( DebugStream& ds, printf manip )
{
    return manip( ds );
}
////////////////////////////////////////////////////////////////////////////////
/*!
  @class  callerInfoマニピュレーター
*/
class callerInfo
{
    friend DebugStream& operator << ( DebugStream& ds, callerInfo manip );

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
    DebugStream& operator ()( DebugStream& ds )
    {
        return ds << printf( "%s(%d) %s:", m_fileName.c_str(), m_lineNumber, m_funcName.c_str() );
    }

private:
    std::string m_fileName;
    long m_lineNumber;
    std::string m_funcName;
};

/*!
  @brief  callerInfoクラスを引数に取るDebugStreamの挿入演算子のオーバーロード
*/
DebugStream& operator << ( DebugStream& ds, callerInfo manip )
{
    return manip( ds );
}
////////////////////////////////////////////////////////////////////////////////
/*!
  @class eachマニピュレーター
*/
class each
{
    friend DebugStream& operator << ( DebugStream& ds, each manip );

public:
    each( const int onceEveryX )
        : m_value( onceEveryX )
    {
    }
private:
    DebugStream& operator ()( DebugStream& ds )
    {
        ds.setOnceEvery( m_value );
        return ds;
    }
private:
    int m_value;
};

/*!
  @brief  eachクラスを引数にとるDebugStreamの挿入演算子のオーバーロード
*/
DebugStream& operator << ( DebugStream& ds, each manip )
{
    return manip( ds );
}

} // namespace dbg
} // namespace izm

#endif // IZM_DBG_DSMANIPULATOR_H
