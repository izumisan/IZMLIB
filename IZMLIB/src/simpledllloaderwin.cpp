/*!
  @file  simpledllloaderwin.cpp
  @brief シンプルDLLローダ(windows用)の実装ファイル
*/
#include "simpledllloaderwin.h"

namespace izm
{

/*!
  @brief  コンストラクタ
*/
SimpleDllLoaderWin::SimpleDllLoaderWin()
    : m_loadFile(), m_handler(0)
{
}

/*!
  @brief  コピーコンストラクタ
*/
SimpleDllLoaderWin::SimpleDllLoaderWin( const SimpleDllLoaderWin& rhs )
    : m_loadFile(rhs.m_loadFile), m_handler(rhs.m_handler)
{
}

/*!
  @brief  デストラクタ
  @note   DLLのアンロードは行わない.
*/
SimpleDllLoaderWin::~SimpleDllLoaderWin()
{
}

/*!
  @brief  代入演算子
*/
SimpleDllLoaderWin& SimpleDllLoaderWin::operator =( const SimpleDllLoaderWin& rhs )
{
    m_loadFile = rhs.m_loadFile;
    m_handler = rhs.m_handler;
    return *this;
}

/*!
  @brief  DLLをロードする.
  @param  [in]  loadFile  DLLファイル
  @return ロード結果(true: 成功, false: 失敗)
*/
bool SimpleDllLoaderWin::load( const std::string& loadFile )
{
    bool result = false;
    if ( ( isLoad() != true ) && ( loadFile != "" ) )
    {
        m_handler = ::LoadLibraryA( loadFile.c_str() );
        if ( m_handler != 0 )
        {
            result = true;
            m_loadFile = loadFile;
        }
    }
    return result;
}

/*!
  @brief  エクスポート関数のポインタを取得する.
  @param  [in]  funcName  関数名
  @return 関数ポインタ
*/
void* SimpleDllLoaderWin::getFunc( const std::string& funcName ) const
{
    void* result = 0;
    if ( m_handler != 0 )
    {
        result = reinterpret_cast<void*>( ::GetProcAddress( m_handler, funcName.c_str() ) );
    }
    return result;
}

/*!
  @brief  DLLをアンロードする.
  @return アンロード結果(true: 成功, false: 失敗)
*/
bool SimpleDllLoaderWin::unload()
{
    bool result = false;
    if ( m_handler != 0 )
    {
        if ( ::FreeLibrary( m_handler ) != 0 )
        {
            result = true;
            m_loadFile.clear();
            m_handler = 0;
        }
    }
    return result;
}

/*!
  @brief  DLLのロード状態を取得する.
  @return ロード状態(true: ロード済み, false: 未ロード)
*/
bool SimpleDllLoaderWin::isLoad() const
{
    return ( m_handler != 0 ) ? true : false;
}

/*!
  @brief  ロードしているDLLのファイル名を取得する.
  @return DLLファイル名
*/
std::string SimpleDllLoaderWin::loadFile() const
{
    return m_loadFile;
}

} // namespace izm
