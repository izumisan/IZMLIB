#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QDebug>
#include "inifilemanager.h"

using namespace izm;


const std::string TEST_INI_FILE_MINI("testdata/testdata_mini.ini");
const std::string TEST_INI_FILE("testdata/testdata.ini");


class IniFileManagerTest : public QObject
{
    Q_OBJECT

public:
    IniFileManagerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_copy_constructor();  // コピーコンストラクタ
    void test_operator_equal();    // operator =
    void test_operator_indexer();  // operator []

    void test_basic_function();  // 基本機能の確認

    void test_sections();
    void test_keys_all();
    void test_keys_each_section();

    void test_save_saveAs();

private:
    IniFileManager* m_mgr;
};

IniFileManagerTest::IniFileManagerTest()
{
}

void IniFileManagerTest::initTestCase()
{
}

void IniFileManagerTest::cleanupTestCase()
{
}

void IniFileManagerTest::init()
{
    m_mgr = new IniFileManager();
}

void IniFileManagerTest::cleanup()
{
    delete m_mgr;
    m_mgr = 0;
}
//==============================================================================
/*!
  @brief  コピーコンストラクタの確認
*/
void IniFileManagerTest::test_copy_constructor()
{
    m_mgr->load( TEST_INI_FILE_MINI );

    IniFileManager dest( *m_mgr );

    QCOMPARE( dest.iniFilePath(), TEST_INI_FILE_MINI );
    QCOMPARE( dest.hasSection("section"), true );
    QCOMPARE( dest.hasKey("section/key"), true );
    QCOMPARE( dest.value("section/key"), std::string("value") );
}
//==============================================================================
/*!
  @brief  代入演算子の確認
*/
void IniFileManagerTest::test_operator_equal()
{
    m_mgr->load( TEST_INI_FILE_MINI );

    IniFileManager dest;
    dest = *m_mgr;

    QCOMPARE( dest.iniFilePath(), TEST_INI_FILE_MINI );
    QCOMPARE( dest.hasSection("section"), true );
    QCOMPARE( dest.hasKey("section/key"), true );
    QCOMPARE( dest.value("section/key"), std::string("value") );
}
//==============================================================================
/*!
  @brief  operator[] の確認
*/
void IniFileManagerTest::test_operator_indexer()
{
    m_mgr->load( TEST_INI_FILE_MINI );

    // 値の取得
    QCOMPARE( (*m_mgr)["section/key"], std::string("value") );

    // 値の上書き
    (*m_mgr)["section/key"] = "hoge";
    QCOMPARE( (*m_mgr)["section/key"], std::string("hoge") );
    QCOMPARE( m_mgr->value("section/key"), std::string("hoge") );

    // key-valueの新規登録
    QCOMPARE( m_mgr->hasKey("sec1/key1"), false );
    (*m_mgr)["sec1/key1"] = "new_value";  // 新規登録
    QCOMPARE( m_mgr->hasKey("sec1/key1"), true );
    QCOMPARE( m_mgr->value("sec1/key1"), std::string("new_value") );
}
//==============================================================================
/*!
*/
void IniFileManagerTest::test_basic_function()
{
    // 拡張子がiniではないファイルはロードしない。
    bool ret = m_mgr->load("hoge");
    QCOMPARE( ret, false );

    // 存在しないファイルはロードしない。
    ret = m_mgr->load("hoge.ini");
    QCOMPARE( ret, false );

    // ロード可能
    ret = m_mgr->load( TEST_INI_FILE_MINI );
    QCOMPARE( ret, true );
    QCOMPARE( m_mgr->iniFilePath(), TEST_INI_FILE_MINI );

    // ロードした TEST_INI_FILE_MINI の中身
    //------------------
    // [section]
    // key = value
    // #comment = dummy
    //------------------
    QCOMPARE( m_mgr->hasSection("section"), true );
    QCOMPARE( m_mgr->hasKey("section", "key"), true );
    QCOMPARE( m_mgr->hasKey("section/key"), true );
    QCOMPARE( m_mgr->value("section", "key"), std::string("value") );
    QCOMPARE( m_mgr->value("section/key"), std::string("value") );

    // コメント行は読み込まない
    QCOMPARE( m_mgr->hasKey("section", "#comment"), false );

    // TEST_INI_FILE_MINI に"key1"というキーは存在しない。
    QCOMPARE( m_mgr->hasKey("", "key1"), false );
    QCOMPARE( m_mgr->hasKey("/key1"), false );

    // 別ファイル(TEST_INI_FILE)をロードすることが出来る。
    ret = m_mgr->load( TEST_INI_FILE );
    QCOMPARE( ret, true );
    QCOMPARE( m_mgr->iniFilePath(), TEST_INI_FILE );

    // ロードした TEST_INI_FILE に"key1"というキーは存在する。
    QCOMPARE( m_mgr->hasKey("", "key1"), true );
    QCOMPARE( m_mgr->hasKey("/key1"), true );

    // ロードしていた TEST_INI_FILE_MINI の情報はクリアされる。
    QCOMPARE( m_mgr->hasSection("section"), false );
    QCOMPARE( m_mgr->hasKey("section", "key"), false );
    QCOMPARE( m_mgr->value("section", "key"), std::string("") );
}
//==============================================================================
/*!
*/
void IniFileManagerTest::test_sections()
{
    m_mgr->load(TEST_INI_FILE);

    std::vector<std::string> sectionList = m_mgr->sections();
    QCOMPARE( sectionList.size(), 4u );

    std::sort( sectionList.begin(), sectionList.end() );
    QCOMPARE( sectionList.at(0), std::string("") );
    QCOMPARE( sectionList.at(1), std::string("section1") );
    QCOMPARE( sectionList.at(2), std::string("section2") );
    QCOMPARE( sectionList.at(3), std::string("section2/subsection21") );
}
//==============================================================================
/*!
*/
void IniFileManagerTest::test_keys_all()
{
    m_mgr->load(TEST_INI_FILE);

    std::vector<std::string> keyList = m_mgr->keys();
    QCOMPARE( keyList.size(), 8u );

    std::sort( keyList.begin(), keyList.end() );
    QCOMPARE( keyList.at(0), std::string("/key1") );
    QCOMPARE( keyList.at(1), std::string("/key2") );
    QCOMPARE( keyList.at(2), std::string("section1/key11") );
    QCOMPARE( keyList.at(3), std::string("section1/key12") );
    QCOMPARE( keyList.at(4), std::string("section2/key21") );
    QCOMPARE( keyList.at(5), std::string("section2/key22") );
    QCOMPARE( keyList.at(6), std::string("section2/subsection21/key211") );
    QCOMPARE( keyList.at(7), std::string("section2/subsection21/key212") );
}
//==============================================================================
/*!
*/
void IniFileManagerTest::test_keys_each_section()
{
    m_mgr->load(TEST_INI_FILE);

    // 無名セクションのキーの確認
    std::vector<std::string> keyList = m_mgr->keys("");
    QCOMPARE( keyList.size(), 2u );

    std::sort( keyList.begin(), keyList.end() );
    QCOMPARE( keyList.at(0), std::string("/key1") );
    QCOMPARE( keyList.at(1), std::string("/key2") );


    // section1のキーの確認
    keyList.clear();
    keyList = m_mgr->keys("section1");
    QCOMPARE( keyList.size(), 2u );

    std::sort( keyList.begin(), keyList.end() );
    QCOMPARE( keyList.at(0), std::string("section1/key11") );
    QCOMPARE( keyList.at(1), std::string("section1/key12") );
}
//==============================================================================
/*!
*/
void IniFileManagerTest::test_save_saveAs()
{
    m_mgr->load(TEST_INI_FILE_MINI);

    // "output.ini"のファイル名で設定情報をINIファイルに出力。
    // 出力したファイルを読み込んで、設定が適切に出力されていることを確認する。
    m_mgr->changeFilePath("output.ini");
    QCOMPARE( m_mgr->save(), true );
    QCOMPARE( m_mgr->load("output.ini"), true );
    QCOMPARE( m_mgr->hasSection("section"), true );
    QCOMPARE( m_mgr->hasKey("section/key"), true );

    // saveAs()の確認。確認方法は同上。
    QCOMPARE( m_mgr->saveAs("output2.ini"), true );
    QCOMPARE( m_mgr->load("output2.ini"), true );
    QCOMPARE( m_mgr->hasSection("section"), true );
    QCOMPARE( m_mgr->hasKey("section/key"), true );
}


QTEST_APPLESS_MAIN(IniFileManagerTest)

#include "tst_inifilemanagertest.moc"
