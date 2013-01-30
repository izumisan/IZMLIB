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
