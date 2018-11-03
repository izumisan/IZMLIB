#include <QString>
#include <QtTest>
#include <QDebug>
#include "enummap.h"

enum class Foo
{
    Foo_1,
    Foo_2,
    Foo_3
};

class EnumMapTest : public QObject
{
    Q_OBJECT

public:
    EnumMapTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void parse_test();
    void parse_throw_exception_for_unregister_string();

    void toString_test();
    void toString_throw_exception_for_unregister_element();

    void isDefined_element_test();
    void isDefined_string_test();
};

EnumMapTest::EnumMapTest()
{
}

void EnumMapTest::initTestCase()
{
}

void EnumMapTest::cleanupTestCase()
{
}

void EnumMapTest::init()
{
}

void EnumMapTest::cleanup()
{
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/*!
*/
void EnumMapTest::parse_test()
{
    auto&& foo = izm::EnumMap<Foo>();
    foo.registerElement( Foo::Foo_1, "Foo_1" );
    foo.registerElement( Foo::Foo_2, "Foo_2" );
    foo.registerElement( Foo::Foo_3, "Foo_3" );

    QCOMPARE( foo.parse( "Foo_1" ), Foo::Foo_1 );
    QCOMPARE( foo.parse( "Foo_2" ), Foo::Foo_2 );
    QCOMPARE( foo.parse( "Foo_3" ), Foo::Foo_3 );
}
//==============================================================================
/*!
*/
void EnumMapTest::parse_throw_exception_for_unregister_string()
{
    auto&& foo = izm::EnumMap<Foo>();
    foo.registerElement( Foo::Foo_1, "Foo_1" );
    foo.registerElement( Foo::Foo_2, "Foo_2" );
    foo.registerElement( Foo::Foo_3, "Foo_3" );

    QVERIFY_EXCEPTION_THROWN( foo.parse( "Bar_1" ), std::invalid_argument );
}
//==============================================================================
/*!
*/
void EnumMapTest::toString_test()
{
    auto&& foo = izm::EnumMap<Foo>
    {
        { Foo::Foo_1, "Foo_1" },
        { Foo::Foo_2, "Foo_2" },
        { Foo::Foo_3, "Foo_3" }
    };

    QCOMPARE( foo.toString( Foo::Foo_1 ).c_str(), "Foo_1" );
    QCOMPARE( foo.toString( Foo::Foo_2 ).c_str(), "Foo_2" );
    QCOMPARE( foo.toString( Foo::Foo_3 ).c_str(), "Foo_3" );
}
//==============================================================================
/*!
*/
void EnumMapTest::toString_throw_exception_for_unregister_element()
{
    auto&& foo = izm::EnumMap<Foo>
    {
        { Foo::Foo_1, "Foo_1" },
        { Foo::Foo_2, "Foo_2" }
    };

    QVERIFY_EXCEPTION_THROWN( foo.toString( Foo::Foo_3 ), std::invalid_argument );
}
//==============================================================================
/*!
*/
void EnumMapTest::isDefined_element_test()
{
    auto&& foo = izm::EnumMap<Foo>
    {
        { Foo::Foo_1, "Foo_1" },
        { Foo::Foo_2, "Foo_2" }
    };

    QCOMPARE( foo.isDefined( Foo::Foo_1 ), true );
    QCOMPARE( foo.isDefined( Foo::Foo_2 ), true );
    QCOMPARE( foo.isDefined( Foo::Foo_3 ), false );
}
//==============================================================================
/*!
*/
void EnumMapTest::isDefined_string_test()
{
    auto&& foo = izm::EnumMap<Foo>
    {
        { Foo::Foo_1, "Foo_1" },
        { Foo::Foo_2, "Foo_2" }
    };

    QCOMPARE( foo.isDefined( "Foo_1" ), true );
    QCOMPARE( foo.isDefined( "Foo_2" ), true );
    QCOMPARE( foo.isDefined( "Foo_3" ), false );
}

QTEST_APPLESS_MAIN(EnumMapTest)

#include "tst_enummaptest.moc"
