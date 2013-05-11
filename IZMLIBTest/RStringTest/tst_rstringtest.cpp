#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QDebug>
#include "rstring.h"

using namespace izm;

class RStringTest : public QObject
{
    Q_OBJECT

public:
    RStringTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_convert_to_integer();
    void test_convert_to_real();

    void test_first_head();
    void test_last_tail();

    void test_include_data();
    void test_include();

    void test_leftPart_rightPart();

    void test_leftPartR_rightPartR();

    void test_upcase_data();
    void test_upcase();

    void test_downcase_data();
    void test_downcase();
};

RStringTest::RStringTest()
{
}

void RStringTest::initTestCase()
{
}

void RStringTest::cleanupTestCase()
{
}

void RStringTest::init()
{
}

void RStringTest::cleanup()
{
}

//==============================================================================
/*
*/
void RStringTest::test_convert_to_integer()
{
    RString obj;
    int expected = 0;

    obj = RString("-10");
    expected = -10;
    QCOMPARE( obj.to_i(), expected );
    QCOMPARE( obj.toInt(), expected );

    obj = RString("10");
    expected = 10;
    QCOMPARE( obj.to_i(), expected );
    QCOMPARE( obj.toInt(), expected );

    obj = RString();
    expected = 0;
    QCOMPARE( obj.to_i(), expected );
    QCOMPARE( obj.toInt(), expected );
}
//==============================================================================
/*
*/
void RStringTest::test_convert_to_real()
{
    RString obj;
    double expected = 0;

    obj = RString("-123.456");
    expected = -123.456;
    QCOMPARE( obj.to_f(), expected );
    QCOMPARE( obj.toDouble(), expected );

    obj = RString("789.012");
    expected = 789.012;
    QCOMPARE( obj.to_f(), expected );
    QCOMPARE( obj.toDouble(), expected );

    obj = RString();
    expected = 0.0;
    QCOMPARE( obj.to_f(), expected );
    QCOMPARE( obj.toDouble(), expected );
}
//==============================================================================
/*
*/
void RStringTest::test_first_head()
{
    RString obj("RString");
    QCOMPARE( obj.first(), 'R' );
    QCOMPARE( obj.head(), 'R' );
}
//==============================================================================
/*
*/
void RStringTest::test_last_tail()
{
    RString obj("RString");
    QCOMPARE( obj.last(), 'g' );
    QCOMPARE( obj.tail(), 'g' );
}
//==============================================================================
/*
*/
void RStringTest::test_include_data()
{
    QTest::addColumn<QString>("_str");
    QTest::addColumn<QString>("_search");
    QTest::addColumn<bool>("_expected");

    QTest::newRow("case1") << "abcdefg" << "cde" << true;
    QTest::newRow("case2") << "abcdefg" << "hij" << false;
    QTest::newRow("case3") << "abcdefg" << "CDE" << false;
    QTest::newRow("case4") << "abcdefg" << "fgh" << false;
}
/*!
*/
void RStringTest::test_include()
{
    QFETCH( QString, _str );
    QFETCH( QString, _search );
    QFETCH( bool, _expected );

    RString obj( _str.toStdString() );

    QCOMPARE( obj.include( _search.toStdString() ), _expected );
}

//==============================================================================
/*!
*/
void RStringTest::test_leftPart_rightPart()
{
    RString obj;

    obj = RString("aaa bbb");
    QCOMPARE( obj.leftPart(" ").to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPart(" ").to_s(), std::string("bbb") );

    // デリミタを指定しない場合、デフォルトのデリミタ(空白)が適用される
    QCOMPARE( obj.leftPart().to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPart().to_s(), std::string("bbb") );

    // デリミタが空文字の場合、空文字となる
    QCOMPARE( obj.leftPart("").to_s(), std::string("") );
    QCOMPARE( obj.rightPart("").to_s(),std::string("") );

    // デリミタは文字列で指定できる
    obj = RString("aaabbbccc");
    QCOMPARE( obj.leftPart("bbb").to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPart("bbb").to_s(), std::string("ccc") );

    // 最初に見つけたデリミタの位置で分割される
    QCOMPARE( obj.leftPart("b").to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPart("b").to_s(), std::string("bbccc") );

    // 指定したデリミタが対象文字列の先頭だった場合、左部分は空文字となる
    obj = RString(",aaa");
    QCOMPARE( obj.leftPart(",").to_s(), std::string("") );
    QCOMPARE( obj.rightPart(",").to_s(), std::string("aaa") );

    // 指定したデリミタが対象文字列の末尾だった場合、右部分は空文字となる
    obj = RString("aaa,");
    QCOMPARE( obj.leftPart(",").to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPart(",").to_s(), std::string("") );

    // デリミタが見つからない場合は、空文字となる
    obj = RString("aaabbb");
    QCOMPARE( obj.leftPart(",").to_s(), std::string("") );
    QCOMPARE( obj.rightPart(",").to_s(), std::string("") );

    //
    // オブジェクトが変更していないことの確認
    //
    obj = RString("aaa bbb");
    obj.leftPart();
    QCOMPARE( obj.to_s(), std::string("aaa bbb") );

    obj = RString("aaa bbb");
    obj.rightPart();
    QCOMPARE( obj.to_s(), std::string("aaa bbb") );

    //
    // 破壊メソッドの確認
    //
    obj = RString("aaa bbb");
    obj.leftPart_d();
    QCOMPARE( obj.to_s(), std::string("aaa") );

    obj = RString("aaa bbb");
    obj.rightPart_d();
    QCOMPARE( obj.to_s(), std::string("bbb") );
}
//==============================================================================
/*!
*/
void RStringTest::test_leftPartR_rightPartR()
{
    RString obj;

    obj = RString("aaa bbb");
    QCOMPARE( obj.leftPartR(" ").to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPartR(" ").to_s(), std::string("bbb") );

    // デリミタを指定しない場合、デフォルトのデリミタ(空白)が適用される
    QCOMPARE( obj.leftPartR().to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPartR().to_s(), std::string("bbb") );

    // デリミタが空文字の場合、空文字となる
    QCOMPARE( obj.leftPartR("").to_s(), std::string("") );
    QCOMPARE( obj.rightPartR("").to_s(),std::string("") );

    // デリミタは文字列で指定できる
    obj = RString("aaabbbccc");
    QCOMPARE( obj.leftPartR("bbb").to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPartR("bbb").to_s(), std::string("ccc") );

    // 最後に見つけたデリミタの位置で分割される
    QCOMPARE( obj.leftPartR("b").to_s(), std::string("aaabb") );
    QCOMPARE( obj.rightPartR("b").to_s(), std::string("ccc") );

    // 指定したデリミタが対象文字列の先頭だった場合、左部分は空文字となる
    obj = RString(",aaa");
    QCOMPARE( obj.leftPartR(",").to_s(), std::string("") );
    QCOMPARE( obj.rightPartR(",").to_s(), std::string("aaa") );

    // 指定したデリミタが対象文字列の末尾だった場合、右部分は空文字となる
    obj = RString("aaa,");
    QCOMPARE( obj.leftPartR(",").to_s(), std::string("aaa") );
    QCOMPARE( obj.rightPartR(",").to_s(), std::string("") );

    // デリミタが見つからない場合は、空文字となる
    obj = RString("aaabbb");
    QCOMPARE( obj.leftPartR(",").to_s(), std::string("") );
    QCOMPARE( obj.rightPartR(",").to_s(), std::string("") );

    //
    // オブジェクトが変更していないことの確認
    //
    obj = RString("aaa bbb");
    obj.leftPartR();
    QCOMPARE( obj.to_s(), std::string("aaa bbb") );

    obj = RString("aaa bbb");
    obj.rightPartR();
    QCOMPARE( obj.to_s(), std::string("aaa bbb") );

    //
    // 破壊メソッドの確認
    //
    obj = RString("aaa bbb");
    obj.leftPartR_d();
    QCOMPARE( obj.to_s(), std::string("aaa") );

    obj = RString("aaa bbb");
    obj.rightPartR_d();
    QCOMPARE( obj.to_s(), std::string("bbb") );
}
//==============================================================================
/*!
*/
void RStringTest::test_upcase_data()
{
    QTest::addColumn<QString>("_str");
    QTest::addColumn<QString>("_expected");

    QTest::newRow("case1") << "a" << "A";
    QTest::newRow("case2") << "A" << "A";
    QTest::newRow("case3") << "abc" << "ABC";
    QTest::newRow("case4") << "aBc" << "ABC";
}
/*!
*/
void RStringTest::test_upcase()
{
    QFETCH( QString, _str );
    QFETCH( QString, _expected );

    RString obj( _str.toStdString() );
    QCOMPARE( obj.upcase().to_s(), _expected.toStdString() );
    QCOMPARE( obj.upcase_d().to_s(), _expected.toStdString() );
}
//==============================================================================
/*!
*/
void RStringTest::test_downcase_data()
{
    QTest::addColumn<QString>("_str");
    QTest::addColumn<QString>("_expected");

    QTest::newRow("case1") << "A" << "a";
    QTest::newRow("case2") << "a" << "a";
    QTest::newRow("case3") << "ABC" << "abc";
    QTest::newRow("case4") << "aBc" << "abc";
}
/*!
*/
void RStringTest::test_downcase()
{
    QFETCH( QString, _str );
    QFETCH( QString, _expected );

    RString obj( _str.toStdString() );
    QCOMPARE( obj.downcase().to_s(), _expected.toStdString() );
    QCOMPARE( obj.downcase_d().to_s(), _expected.toStdString() );
}


QTEST_APPLESS_MAIN(RStringTest);

#include "tst_rstringtest.moc"
