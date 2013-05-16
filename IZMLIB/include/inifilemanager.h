/*!
  @file  inifilemanager.h
  @brief INIファイル管理クラスのヘッダファイル
*/
#ifndef IZM_INIFILEMANAGER_H
#define IZM_INIFILEMANAGER_H

#include <string>
#include <vector>

namespace izm
{

namespace internal
{
class IniFileManagerImpl;  // 前方宣言
}

class IniFileManager
{
    //  静的メソッド
    //--------------------------------------------------------------------------
public:
    static IniFileManager * const instance();


    //  コンストラクタ・デストラクタ
    //--------------------------------------------------------------------------
protected:
    IniFileManager();
private:
    IniFileManager( const IniFileManager& rhs );  // 使用禁止
public:
    virtual ~IniFileManager();


    //  演算子
    //--------------------------------------------------------------------------
private:
    IniFileManager& operator =( const IniFileManager& rhs );  // 使用禁止
public:
    //std::string& operator []( const std::string& key );

    //  操作
    //--------------------------------------------------------------------------
public:
    bool load( const std::string& loadFile );

    bool hasSection( const std::string& section ) const;
    bool hasKey( const std::string& key ) const;
    bool hasKey( const std::string& section, const std::string& key ) const;

    std::string value( const std::string& key ) const;
    std::string value( const std::string& section, const std::string& key ) const;

    std::vector<std::string> sections() const;
    std::vector<std::string> keys() const;
    std::vector<std::string> keys( const std::string& section ) const;

    std::string iniFilePath() const;
    bool changeFilePath( const std::string& newFilePath );

    bool save() const;
    bool saveAs( const std::string& otherFilePath );

    void setValue( const std::string& key, const std::string& value );
    void setValue( const std::string& section, const std::string& key, const std::string& value );


    //  メンバ変数
    //--------------------------------------------------------------------------
private:
    internal::IniFileManagerImpl* m_impl;
};

} // namespace izm

#endif // IZM_INIFILEMANAGER_H
