/*!
  @file  inifilemanagerimpl.h
  @brief INIファイル管理クラス(内部)のヘッダファイル
*/
#ifndef INTERNAL_INIFILEMANAGERIMPL_H
#define INTERNAL_INIFILEMANAGERIMPL_H

#include <map>
#include "rstring.h"

namespace izm
{
namespace internal
{

class IniFileManagerImpl
{
    //  コンストラクタ・デストラクタ
    //--------------------------------------------------------------------------
public:
    IniFileManagerImpl();
    explicit IniFileManagerImpl( const IniFileManagerImpl& rhs );
    virtual ~IniFileManagerImpl();

    //  演算子
    //--------------------------------------------------------------------------
public:
    IniFileManagerImpl& operator = ( const IniFileManagerImpl& rhs );
    RString& operator []( const RString& key );

    //  操作
    //--------------------------------------------------------------------------
public:
    bool load( const RString& loadFile );

    bool hasSection( const RString& section ) const;
    bool hasKey( const RString& key ) const;
    bool hasKey( const RString& section, const RString& key ) const;

    RString value( const RString& key ) const;
    RString value( const RString& section, const RString& key ) const;

    void sections( std::vector<RString>& sectionList ) const;
    void keys( std::vector<RString>& keyList ) const;
    void keys( const RString& section, std::vector<RString>& keyList ) const;

    RString iniFilePath() const;
    void changeFilePath( const RString& newFilePath );

    bool save() const;
    bool saveAs( const RString& newFilePath );

    void setValue( const RString& key, const RString& value );
    void setValue( const RString& section, const RString& key, const RString& value );

private:
    void clear();
    void copyToMe( const IniFileManagerImpl& rhs );
    bool setupData( const RString& iniFilePath );
    bool registerKeyValue( const RString& key, const RString& value );
    bool checkExtension( const RString& loadFile ) const;

    //  フィールド
    //--------------------------------------------------------------------------
private:
    RString m_iniFilePath;
    std::map<RString, RString>* m_data;
};

} // namespace internal
} // namespace izm

#endif // INTERNAL_INIFILEMANAGERIMPL_H
