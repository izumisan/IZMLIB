#include <QString>
#include <QtTest>

#include "literals.h"

class LiteralsTest : public QObject
{
    Q_OBJECT

public:
    LiteralsTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void angleLiteralsTest();
    void lengthLiteralsTest();
};

LiteralsTest::LiteralsTest()
{
}

void LiteralsTest::initTestCase()
{
}

void LiteralsTest::cleanupTestCase()
{
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/*!
  @brief  アングルリテラルのテスト
*/
void LiteralsTest::angleLiteralsTest()
{
    double&& one_deg = 1.0_deg;
    double&& one_rad = 1.0_rad;

    const double&& pi = 4.0 * std::atan( 1.0 );

    QCOMPARE( one_deg, pi / 180.0 );
    QCOMPARE( one_rad, 1.0 );
}
//==============================================================================
/*!
  @brief レンジリテラルのテスト
*/
void LiteralsTest::lengthLiteralsTest()
{
    constexpr double one_km = 1.0_km;
    constexpr double one_m = 1.0_m;
    constexpr double one_cm = 1.0_cm;
    constexpr double one_mm = 1.0_mm;

    QCOMPARE( one_km, 1000.0 );
    QCOMPARE( one_m, 1.0 );
    QCOMPARE( one_cm, 0.01 );
    QCOMPARE( one_mm, 0.001 );
}

QTEST_APPLESS_MAIN(LiteralsTest)

#include "tst_literalstest.moc"
