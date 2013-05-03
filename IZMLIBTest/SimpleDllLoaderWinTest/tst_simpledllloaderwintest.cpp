#include <QtCore/QString>
#include <QtTest/QtTest>

#include <string>
#include "testdll.h"

#include "simpledllloaderwin.h"

using namespace izm;

const std::string DLL_FILE_PATH("TestDLL/debug/TestDLL.dll");

class SimpleDllLoaderWinTest : public QObject
{
    Q_OBJECT

public:
    SimpleDllLoaderWinTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // loadメソッドのテスト
    void loadTest_normal();
    void loadTest_load_2times();
    void loadTest_file_name_is_empty();
    void loadTest_non_existent_file();
    // getFuncメソッドのテスト
    void getFuncTest();
    // isLoadメソッドのテスト
    void isLoadTest();
    // loadFileメソッドのテスト
    void loadFileTest();

private:
    SimpleDllLoaderWin* m_loader;
};

SimpleDllLoaderWinTest::SimpleDllLoaderWinTest()
    : m_loader(0)
{
}

void SimpleDllLoaderWinTest::initTestCase()
{
}

void SimpleDllLoaderWinTest::cleanupTestCase()
{
}

void SimpleDllLoaderWinTest::init()
{
    m_loader = new SimpleDllLoaderWin();
}

void SimpleDllLoaderWinTest::cleanup()
{
    m_loader->unload();
    delete m_loader;
}
//==============================================================================
void SimpleDllLoaderWinTest::loadTest_normal()
{
    bool loadResult = m_loader->load( DLL_FILE_PATH );
    QCOMPARE( loadResult, true );
}
//==============================================================================
void SimpleDllLoaderWinTest::loadTest_load_2times()
{
    bool loadResult1 = m_loader->load( DLL_FILE_PATH );
    QCOMPARE( loadResult1, true );

    // アンロードせずに再度ロードすることは許さない。
    bool loadResult2 = m_loader->load( DLL_FILE_PATH );
    QCOMPARE( loadResult2, false );
}
//==============================================================================
void SimpleDllLoaderWinTest::loadTest_file_name_is_empty()
{
    bool loadResult = m_loader->load("");
    QCOMPARE( loadResult, false );
}
//==============================================================================
void SimpleDllLoaderWinTest::loadTest_non_existent_file()
{
    // 存在しないDLLはロードできない。
    bool loadResult = m_loader->load("hoge.dll");
    QCOMPARE( loadResult, false );
}
//==============================================================================
void SimpleDllLoaderWinTest::getFuncTest()
{
    // load前にgetFuncメソッドを呼び出すとNULLとなる。
    std::string funcName("hogeMethod");
    void* getFuncResult = m_loader->getFunc( funcName );
    QVERIFY( getFuncResult == 0 );

    // 存在しない関数名を指定するとNULLとなる。
    m_loader->load( DLL_FILE_PATH );
    getFuncResult = m_loader->getFunc( funcName );
    QVERIFY( getFuncResult == 0 );

    // TestDLL.dllのGetNext関数を実行する。
    getFuncResult = m_loader->getFunc("GetNext");
    int (*func)(int) = reinterpret_cast<int (*)(int)>( getFuncResult );
    int funcResult = func( 10 );
    QCOMPARE( funcResult, 11 );

    // TestDLL.dllのGetPrevious関数を実行する。
    getFuncResult = m_loader->getFunc("GetPrevious");
    func = reinterpret_cast<int (*)(int)>( getFuncResult );
    funcResult = func( 10 );
    QCOMPARE( funcResult, 9 );
}
//==============================================================================
void SimpleDllLoaderWinTest::isLoadTest()
{
    // ロード前
    bool loadStatus = m_loader->isLoad();
    QCOMPARE( loadStatus, false );

    // ロード後
    m_loader->load( DLL_FILE_PATH );
    loadStatus = m_loader->isLoad();
    QCOMPARE( loadStatus, true );

    // アンロード後
    m_loader->unload();
    loadStatus = m_loader->isLoad();
    QCOMPARE( loadStatus, false );
}
//==============================================================================
void SimpleDllLoaderWinTest::loadFileTest()
{
    // ロード前
    std::string actual = m_loader->loadFile();
    QVERIFY( actual == "" );

    // ロード後
    m_loader->load( DLL_FILE_PATH );
    actual = m_loader->loadFile();
    QVERIFY( actual == DLL_FILE_PATH );

    // アンロード後
    m_loader->unload();
    actual = m_loader->loadFile();
    QVERIFY( actual == "" );
}


QTEST_APPLESS_MAIN(SimpleDllLoaderWinTest)

#include "tst_simpledllloaderwintest.moc"
