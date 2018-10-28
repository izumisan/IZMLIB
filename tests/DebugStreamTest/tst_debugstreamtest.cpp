#include <QString>
#include <QtTest>
#include <QFile>
#include <QDebug>

#include "debugstream.h"

class DebugStreamTest : public QObject
{
    Q_OBJECT

public:
    DebugStreamTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void should_be_set_default_path();
    void should_be_set_assigned_path();
};

DebugStreamTest::DebugStreamTest()
{
}

void DebugStreamTest::initTestCase()
{
}

void DebugStreamTest::cleanupTestCase()
{
}

void DebugStreamTest::init()
{
}

void DebugStreamTest::cleanup()
{
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/*!
*/
void DebugStreamTest::should_be_set_default_path()
{
    const QString expected( "izm.debug.log" );
    if ( QFile::exists( expected ) )
    {
        QFile::remove( expected );
    }
    QCOMPARE( QFile::exists( expected ), false );

    auto&& stream = izm::dbg::DebugStream();
    stream << "Hello World";
    stream.eol();
    stream << "int:" << 1;
    stream.eol();
    stream << "double:" << 1.1;
    stream.eol();

    QCOMPARE( stream.path().c_str(), expected );
    QCOMPARE( QFile::exists( expected ), true );
}
//==============================================================================
/*!
*/
void DebugStreamTest::should_be_set_assigned_path()
{
    const QString&& expected = QString( QTest::currentTestFunction() ) + ".log";
    if ( QFile::exists( expected ) )
    {
        QFile::remove( expected );
    }
    QCOMPARE( QFile::exists( expected ), false );

    auto&& stream = izm::dbg::DebugStream( expected.toStdString() );
    stream << QTest::currentTestFunction();
    stream.eol();
    stream << "int:" << 1;
    stream.eol();
    stream << "double:" << 1.1;
    stream.eol();

    QCOMPARE( stream.path().c_str(), expected );
    QCOMPARE( QFile::exists( expected ), true );
}


QTEST_APPLESS_MAIN(DebugStreamTest)

#include "tst_debugstreamtest.moc"
