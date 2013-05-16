/*!
  @file  inifilemanagerimpl.cpp
  @brief INIファイル管理クラス(内部)の実装ファイル
*/
#include <fstream>
#include <algorithm>
#include "rstring.h"

#include "inifilemanagerimpl.h"

namespace izm
{
namespace internal
{

//  コンストラクタ・デストラクタ
//------------------------------------------------------------------------------
/*!
  @brief  コンストラクタ
*/
IniFileManagerImpl::IniFileManagerImpl()
    : m_iniFilePath()
    , m_data(0)
{
    m_data = new std::map<RString, RString>();
}

/*!
  @brief  コンストラクタ
*/
IniFileManagerImpl::IniFileManagerImpl( const IniFileManagerImpl& rhs )
    : m_iniFilePath()
    , m_data(0)
{
    m_data = new std::map<RString, RString>();
    copyToMe( rhs );
}

/*!
  @brief  デストラクタ
*/
IniFileManagerImpl::~IniFileManagerImpl()
{
    if ( m_data != 0 )
    {
        delete m_data;
    }
}

//  演算子
//------------------------------------------------------------------------------
/*!
  @brief  代入演算子
*/
IniFileManagerImpl& IniFileManagerImpl::operator = ( const IniFileManagerImpl& rhs )
{
    copyToMe( rhs );
    return *this;
}

/*!
*/
//RString& IniFileManagerImpl::operator []( const RString& key )
//{
//    return m_data->find( key )->second;
//}

//  操作
//------------------------------------------------------------------------------
/*!
*/
bool IniFileManagerImpl::load( const RString& loadFile )
{
    bool result = false;
    if ( checkExtension( loadFile ) )
    {
        clear();
        result = setupData( loadFile );
    }
    return result;
}

/*!
*/
bool IniFileManagerImpl::hasSection( const RString& section ) const
{
    bool result = false;
    for ( std::map<RString, RString>::const_iterator it = m_data->begin();
          it != m_data->end();
          ++it )
    {
        RString sectionOfKey = (it->first).leftPartR("/");
        if ( sectionOfKey == section )
        {
            result = true;
            break;
        }
    }
    return result;
}

/*!
*/
bool IniFileManagerImpl::hasKey( const RString& key ) const
{
    bool result = false;
    std::map<RString, RString>::const_iterator it = m_data->find( key );
    if ( it != m_data->end() )
    {
        result = true;
    }
    return result;
}

/*!
*/
bool IniFileManagerImpl::hasKey( const RString& section, const RString& key ) const
{
    return hasKey( section + "/" + key );
}

/*!
*/
RString IniFileManagerImpl::value( const RString& key ) const
{
    RString result;
    if ( m_data != 0 )
    {
        std::map<RString, RString>::const_iterator it = m_data->find( key );
        if ( it != m_data->end() )
        {
            result = it->second;
        }
    }
    return result;
}

/*!
*/
RString IniFileManagerImpl::value( const RString& section, const RString& key ) const
{
    return value( section + "/" + key );
}

/*!
*/
void IniFileManagerImpl::sections( std::vector<RString>& sectionList ) const
{
    for ( std::map<RString, RString>::const_iterator it = m_data->begin();
          it != m_data->end();
          ++it )
    {
        RString sectionOfKey = (it->first).leftPartR("/");

        std::vector<RString>::iterator sectionListIter = std::find( sectionList.begin(), sectionList.end(), sectionOfKey );
        if ( sectionListIter == sectionList.end() )
        {
            sectionList.push_back( sectionOfKey );
        }
    }
}

/*!
*/
void IniFileManagerImpl::keys( std::vector<RString>& keyList ) const
{
    for ( std::map<RString, RString>::const_iterator it = m_data->begin();
          it != m_data->end();
          ++it )
    {
        keyList.push_back( it->first );
    }
}

/*!
*/
void IniFileManagerImpl::keys( const RString& section, std::vector<RString>& keyList ) const
{
    for ( std::map<RString, RString>::const_iterator it = m_data->begin();
          it != m_data->end();
          ++it )
    {
        RString sectionOfKey = (it->first).leftPartR("/");
        if ( sectionOfKey == section )
        {
            keyList.push_back( it->first );
        }
    }
}

/*!
*/
RString IniFileManagerImpl::iniFilePath() const
{
    return m_iniFilePath;
}

/*!
*/
void IniFileManagerImpl::changeFilePath( const RString& newFilePath )
{
    m_iniFilePath = newFilePath;
}

/*!
*/
bool IniFileManagerImpl::save() const
{
    bool result = false;
    std::ofstream of( m_iniFilePath );
    if ( of.is_open() )
    {
        std::vector<RString> allSection;
        sections( allSection );

        for ( std::vector<RString>::iterator secIter = allSection.begin();
              secIter != allSection.end();
              ++secIter )
        {
            if ( secIter->size() != 0 )
            {
                of << "[" << *secIter << "]" << std::endl;
            }
            std::vector<RString> keysOfSection;
            keys( *secIter, keysOfSection );
            for ( std::vector<RString>::iterator keyIter = keysOfSection.begin();
                  keyIter != keysOfSection.end();
                  ++keyIter )
            {
                of << (*keyIter).rightPartR("/") << "=" << value(*keyIter) << std::endl;
            }
        }
        result = true;
    }
    return result;
}

/*!
*/
bool IniFileManagerImpl::saveAs( const RString& otherFilePath )
{
    bool result = false;
    m_iniFilePath = otherFilePath;
    result = save();
    return result;
}

/*!
*/
void IniFileManagerImpl::setValue( const RString& key, const RString& value )
{
    // keyが未登録の場合、key-valueを登録する.
    // keyが登録済みの場合、そのkeyのvalueを上書きする.

    std::map<RString, RString>::iterator it = m_data->find( key );
    if ( it == m_data->end() )
    {
        m_data->insert( std::pair<RString, RString>( key, value ) );
    }
    else
    {
        it->second = value;
    }
}

/*!
*/
void IniFileManagerImpl::setValue( const RString& section, const RString& key, const RString& value )
{
    const RString managedKey = section + "/" + key;
    setValue( managedKey, value );
}

//  private
//------------------------------------------------------------------------------
/*!
*/
void IniFileManagerImpl::clear()
{
    m_iniFilePath.clear();
    m_data->clear();
}

/*!
*/
void IniFileManagerImpl::copyToMe( const IniFileManagerImpl& rhs )
{
    m_iniFilePath = rhs.m_iniFilePath;
    for ( std::map<RString, RString>::iterator it = rhs.m_data->begin();
          it != rhs.m_data->end();
          ++it )
    {
        m_data->insert(*it);
    }
}

/*!
*/
bool IniFileManagerImpl::setupData( const RString& iniFile )
{
    bool result = false;
    std::ifstream ifs( iniFile.c_str() );
    if ( ifs.is_open() )
    {
        m_iniFilePath = iniFile;
        result = true;

        RString currentSection;
        RString data;
        while ( std::getline( ifs, data ) )
        {
            // 行頭文字が'#'の行はコメント行と解釈して読み込まない。
            if ( data.first() == '#' )
            {
                continue;
            }

            data.trim_d();
            if ( ( data.first() == '[' ) && ( data.last() == ']' ) )
            {
                data.shift_d();
                data.unshift_d();
                currentSection = data.trim();
            }

            std::vector<RString> dataList = data.split("=");
            if ( dataList.size() == 2 )
            {
                RString key = currentSection + "/" + dataList[0].trim();
                RString val = dataList[1].trim();
                bool nonDuplicate = registerKeyValue( key, val );

                // キーが重複している場合、INIファイルとして正しくないのでセットアップエラーとする。
                if ( nonDuplicate != true )
                {
                    result = false;
                    clear();
                    break;
                }
            }
        }
    }
    return result;
}

/*!
*/
bool IniFileManagerImpl::registerKeyValue( const RString& key, const RString& value )
{
    // key-valueを登録する。
    // keyが重複している場合は登録しない。

    bool result = false;
    std::map<RString, RString>::iterator it = m_data->find( key );
    if ( it == m_data->end() )
    {
        result = true;
        m_data->insert( std::pair<RString, RString>( key, value ) );
    }
    return result;
}

/*!
*/
bool IniFileManagerImpl::checkExtension( const RString& loadFile ) const
{
    bool result = false;
    if ( 4 < loadFile.size() )
    {
        if ( loadFile.include(".ini") )
        {
            result = true;
        }
    }
    return result;
}


} // namespace internal
} // namespace izm
