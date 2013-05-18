/*!
  @file  inifilemanager.cpp
  @brief INIファイル管理クラスの実装ファイル
*/
#include <algorithm>
#include "rstring.h"
#include "inifilemanagerimpl.h"

#include "inifilemanager.h"

namespace izm
{

//  コンストラクタ・デストラクタ
//------------------------------------------------------------------------------
/*!
  @brief  コンストラクタ
*/
IniFileManager::IniFileManager()
    : m_impl(new internal::IniFileManagerImpl())
{
}

/*!
  @brief  コピーコンストラクタ
*/
IniFileManager::IniFileManager( const IniFileManager& rhs )
    : m_impl(new internal::IniFileManagerImpl())
{
    *m_impl = *(rhs.m_impl);
}

/*!
  @brief  デストラクタ
*/
IniFileManager::~IniFileManager()
{
    if ( m_impl != 0 )
    {
        delete m_impl;
    }
}

//  演算子
//------------------------------------------------------------------------------
/*!
  @brief  代入演算子
*/
IniFileManager& IniFileManager::operator =( const IniFileManager& rhs )
{
    *m_impl = *(rhs.m_impl);
    return *this;
}

/*!
  @brief  operator []
*/
std::string& IniFileManager::operator []( const std::string& key )
{
    return (*m_impl)[key];
}

//  操作
//------------------------------------------------------------------------------
/*!
  @brief  指定したファイルをロードする.
  @param  [in]  loadFile  ロードするファイル
  @return ロード結果(true: 成功, false: 失敗)
*/
bool IniFileManager::load( const std::string& loadFile )
{
    return ( m_impl != 0 ) ? m_impl->load( loadFile ) : false;
}

/*!
*/
bool IniFileManager::hasSection( const std::string& section ) const
{
    return ( m_impl != 0 ) ? m_impl->hasSection( section ) : false;
}

/*!
*/
bool IniFileManager::hasKey( const std::string& key ) const
{
    return ( m_impl != 0 ) ? m_impl->hasKey( key ) : false;
}

/*!
*/
bool IniFileManager::hasKey( const std::string& section, const std::string& key ) const
{
    return ( m_impl != 0 ) ? m_impl->hasKey( section, key ) : false;
}

/*!
*/
std::string IniFileManager::value( const std::string& key ) const
{
    std::string result;
    if ( m_impl != 0 )
    {
        result = m_impl->value( key );
    }
    return result;
}

/*!
*/
std::string IniFileManager::value( const std::string& section, const std::string& key ) const
{
    std::string result;
    if ( m_impl != 0 )
    {
        result = m_impl->value( section, key );
    }
    return result;
}

/*!
*/
std::vector<std::string> IniFileManager::sections() const
{
    std::vector<std::string> result;
    if ( m_impl != 0 )
    {
        std::vector<RString> rsList;
        m_impl->sections( rsList );

        // rsListを複製する.
        result.resize( rsList.size() );
        std::copy( rsList.begin(), rsList.end(), result.begin() );
    }
    return result;
}

/*!
*/
std::vector<std::string> IniFileManager::keys() const
{
    std::vector<std::string> result;
    if ( m_impl != 0 )
    {
        std::vector<RString> rsList;
        m_impl->keys( rsList );

        // rsListを複製する.
        result.resize( rsList.size() );
        std::copy( rsList.begin(), rsList.end(), result.begin() );
    }
    return result;
}

/*!
*/
std::vector<std::string> IniFileManager::keys( const std::string& section ) const
{
    std::vector<std::string> result;
    if ( m_impl != 0 )
    {
        std::vector<RString> rsList;
        m_impl->keys( section, rsList );

        // rsListを複製する.
        result.resize( rsList.size() );
        std::copy( rsList.begin(), rsList.end(), result.begin() );
    }
    return result;
}

/*!
  @brief  INIファイルパスを取得する.
  @return INIファイルパス
*/
std::string IniFileManager::iniFilePath() const
{
    std::string result;
    if ( m_impl != 0 )
    {
        result = m_impl->iniFilePath();
    }
    return result;
}

/*!
*/
bool IniFileManager::changeFilePath( const std::string& newFilePath )
{
    bool result = false;
    if ( m_impl != 0 )
    {
        m_impl->changeFilePath( newFilePath );
        result = true;
    }
    return result;
}

/*!
*/
bool IniFileManager::save() const
{
    return ( m_impl != 0 ) ? m_impl->save() : false;
}

/*!
*/
bool IniFileManager::saveAs( const std::string& otherFilePath )
{
    return ( m_impl != 0 ) ? m_impl->saveAs( otherFilePath ) : false;
}

/*!
*/
void IniFileManager::setValue( const std::string& key, const std::string& value )
{
    if ( m_impl != 0 )
    {
        m_impl->setValue( key, value );
    }
}

/*!
*/
void IniFileManager::setValue( const std::string& section, const std::string& key, const std::string& value )
{
    if ( m_impl != 0 )
    {
        m_impl->setValue( section, key, value );
    }
}

} // namespace izm
