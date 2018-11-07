#include <QtCore/QString>
#include <QtTest/QtTest>

#include <string>
#include <vector>
#include "util.h"

class UtilTest : public QObject
{
    Q_OBJECT

public:
    UtilTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_split();

    void replace_test_data();
    void replace_test();

    void test_trim_ltrim_rtrim();
};

UtilTest::UtilTest()
{
}

void UtilTest::initTestCase()
{
}

void UtilTest::cleanupTestCase()
{
}

void UtilTest::init()
{
}

void UtilTest::cleanup()
{
}

//==============================================================================
/*
*/
void UtilTest::test_split()
{
    std::vector<std::string> strList;

    strList = izm::split( "aaa bbb ccc" );
    QCOMPARE( strList.at(0).c_str(), "aaa" );
    QCOMPARE( strList.at(1).c_str(), "bbb" );
    QCOMPARE( strList.at(2).c_str(), "ccc" );

    strList = izm::split( "aaa bbb ccc", " " );
    QCOMPARE( strList.at(0).c_str(), "aaa" );
    QCOMPARE( strList.at(1).c_str(), "bbb" );
    QCOMPARE( strList.at(2).c_str(), "ccc" );

    strList = izm::split( ",,aaa,,,,bbb,,,,,ccc,,,,,,,", ",");
    QCOMPARE( strList.at(0).c_str(), "aaa" );
    QCOMPARE( strList.at(1).c_str(), "bbb" );
    QCOMPARE( strList.at(2).c_str(), "ccc" );
}
//==============================================================================
/*
*/
void UtilTest::replace_test_data()
{
    QTest::addColumn<QString>("_input");
    QTest::addColumn<QString>("_before");
    QTest::addColumn<QString>("_after");
    QTest::addColumn<QString>("_expected");

    QTest::newRow("case1") << "abcde" << "bcd" << "XYZ" << "aXYZe";
    QTest::newRow("case2") << "abcdeabcde" << "bcd" << "XYZ" << "aXYZeaXYZe";
    QTest::newRow("case3") << "a b c d e" << " " << "" << "abcde";
    QTest::newRow("case4") << "a b c d e" << "" << "X" << "a b c d e";
    QTest::newRow("case5") << "xxx" << "x" << "xxx" << "xxxxxxxxx";
}
/*
*/
void UtilTest::replace_test()
{
    QFETCH( QString, _input );
    QFETCH( QString, _before );
    QFETCH( QString, _after );
    QFETCH( QString, _expected );

    auto&& actual = izm::replace( _input.toStdString(),
                                  _before.toStdString(),
                                  _after.toStdString() );

    QCOMPARE( actual, _expected.toStdString() );
}
//==============================================================================
/*
*/
void UtilTest::test_trim_ltrim_rtrim()
{
    std::string str;

    str = " abc ";
    QCOMPARE( izm::trim(str),  std::string("abc") );
    QCOMPARE( izm::ltrim(str), std::string("abc ") );
    QCOMPARE( izm::rtrim(str), std::string(" abc") );

    str = "   abc   ";
    QCOMPARE( izm::trim(str),  std::string("abc") );
    QCOMPARE( izm::ltrim(str), std::string("abc   ") );
    QCOMPARE( izm::rtrim(str), std::string("   abc") );

    str = " \f\n\r\t\vAAA \f\n\r\t\v";
    QCOMPARE( izm::trim(str),  std::string("AAA") );
    QCOMPARE( izm::ltrim(str), std::string("AAA \f\n\r\t\v") );
    QCOMPARE( izm::rtrim(str), std::string(" \f\n\r\t\vAAA") );
}

QTEST_APPLESS_MAIN(UtilTest);

#include "tst_utiltest.moc"
