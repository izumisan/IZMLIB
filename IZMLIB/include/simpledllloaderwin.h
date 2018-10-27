/*!
  @file  simpledllloaderwin.h
  @brief シンプルDLLローダ(windows用)のヘッダファイル
*/
#ifndef IZM_SIMPLEDLLLOADERWIN_H
#define IZM_SIMPLEDLLLOADERWIN_H

#include <string>
#include <Windows.h>

namespace izm
{

class SimpleDllLoaderWin
{
public:
    SimpleDllLoaderWin();
    virtual ~SimpleDllLoaderWin();
private:
    SimpleDllLoaderWin( const SimpleDllLoaderWin& rhs );  // コピー禁止

private:
    SimpleDllLoaderWin& operator =( const SimpleDllLoaderWin& rhs );  // コピー禁止

public:
    bool load( const std::string& loadFile );
    void* getFunc( const std::string& funcName ) const;
    bool unload();

    bool isLoad() const;
    std::string loadFile() const;

private:
    std::string m_loadFile;  //!< DLLファイル名
    HINSTANCE m_handler;     //!< DLLハンドラ
};

} // namespace izm

#endif // IZM_SIMPLEDLLLOADERWIN_H
