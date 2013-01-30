#include <QtCore/QString>
#include <QtTest/QtTest>

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

    void test_first_last();

    void test_dividedLeftPart_dividedRightPart();
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
}
//==============================================================================
/*
*/
void RStringTest::test_first_last()
{
    RString obj("RString");
    QCOMPARE( obj.first(), 'R' );
    QCOMPARE( obj.last(), 'g' );
}
//==============================================================================
/*!
*/
void RStringTest::test_dividedLeftPart_dividedRightPart()
{
    RString obj;

    obj = RString("aaa bbb");
    QCOMPARE( obj.dividedLeftPart().to_s(), std::string("aaa") );
    QCOMPARE( obj.dividedRightPart().to_s(), std::string("bbb") );

    QCOMPARE( obj.dividedLeftPart(" ").to_s(), std::string("aaa") );
    QCOMPARE( obj.dividedRightPart(" ").to_s(), std::string("bbb") );

    obj = RString("aaabbbccc");
    QCOMPARE( obj.dividedLeftPart("bbb").to_s(), std::string("aaa") );
    QCOMPARE( obj.dividedRightPart("bbb").to_s(), std::string("ccc") );

    obj = RString(",aaa");
    QCOMPARE( obj.dividedLeftPart(",").to_s(), std::string("") );
    QCOMPARE( obj.dividedRightPart(",").to_s(), std::string("aaa") );

    obj = RString("aaa,");
    QCOMPARE( obj.dividedLeftPart(",").to_s(), std::string("aaa") );
    QCOMPARE( obj.dividedRightPart(",").to_s(), std::string("") );

    obj = RString("aaabbb");
    QCOMPARE( obj.dividedLeftPart(",").to_s(), std::string("aaabbb") );
    QCOMPARE( obj.dividedRightPart(",").to_s(), std::string("aaabbb") );
}

QTEST_APPLESS_MAIN(RStringTest);

#include "tst_rstringtest.moc"
