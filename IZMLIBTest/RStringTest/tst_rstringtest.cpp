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

QTEST_APPLESS_MAIN(RStringTest);

#include "tst_rstringtest.moc"
