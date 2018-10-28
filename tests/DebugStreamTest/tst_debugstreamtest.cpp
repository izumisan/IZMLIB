#include <QString>
#include <QtTest>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <QDebug>

#include "dbg.h"

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

    void endlTest();
    void timestampTest();
    void callerInfoTest();
    void printfTest();
    void everyTest();

private:
    QList<QString> fileContents( const QString& path ) const;
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
    const auto&& path = std::string( "izm.debug.log" );
    QFile logfile( path.c_str() );
    if ( logfile.exists() )
    {
        logfile.remove();
    }
    QCOMPARE( logfile.exists(), false );

    auto&& stream = izm::dbg::DebugStream();
    stream << "Hello World";
    stream.eol();
    stream << "int:" << 1;
    stream.eol();
    stream << "double:" << 1.1;
    stream.eol();

    QCOMPARE( stream.path().c_str(), path.c_str() );
    QCOMPARE( logfile.exists(), true );
}
//==============================================================================
/*!
*/
void DebugStreamTest::should_be_set_assigned_path()
{
    const auto&& path = std::string( QTest::currentTestFunction() ) + ".log";
    QFile logfile( path.c_str() );
    if ( logfile.exists() )
    {
        logfile.remove();
    }
    QCOMPARE( logfile.exists(), false );

    auto&& stream = izm::dbg::DebugStream( path );
    stream << QTest::currentTestFunction();
    stream.eol();
    stream << "int:" << 1;
    stream.eol();
    stream << "double:" << 1.1;
    stream.eol();

    QCOMPARE( stream.path().c_str(), path.c_str() );
    QCOMPARE( logfile.exists(), true );
}
//==============================================================================
/*!
*/
void DebugStreamTest::endlTest()
{
    const auto&& path = std::string( QTest::currentTestFunction() ) + ".log";
    QFile logfile( path.c_str() );
    if ( logfile.exists() )
    {
        logfile.remove();
    }
    QCOMPARE( logfile.exists(), false );

    auto&& stream = izm::dbg::DebugStream( path );
    for ( int i = 0; i < 10; ++i )
    {
        stream << i << izm::endl;
    }

    QCOMPARE( logfile.exists(), true );

    auto&& contents = fileContents( logfile.fileName() );
    QCOMPARE( contents.size(), 10 );
}
//==============================================================================
/*!
*/
void DebugStreamTest::timestampTest()
{
    const auto&& path = std::string( QTest::currentTestFunction() ) + ".log";
    QFile logfile( path.c_str() );
    if ( logfile.exists() )
    {
        logfile.remove();
    }
    QCOMPARE( logfile.exists(), false );

    //@@@ TODO
}
//==============================================================================
/*!
*/
void DebugStreamTest::callerInfoTest()
{
    const auto&& path = std::string( QTest::currentTestFunction() ) + ".log";
    QFile logfile( path.c_str() );
    if ( logfile.exists() )
    {
        logfile.remove();
    }
    QCOMPARE( logfile.exists(), false );

    //@@@ TODO
}
//==============================================================================
/*!
*/
void DebugStreamTest::printfTest()
{
    const auto&& path = std::string( QTest::currentTestFunction() ) + ".log";
    QFile logfile( path.c_str() );
    if ( logfile.exists() )
    {
        logfile.remove();
    }
    QCOMPARE( logfile.exists(), false );

    //@@@ TODO
}
//==============================================================================
/*!
*/
void DebugStreamTest::everyTest()
{
    const auto&& path = std::string( QTest::currentTestFunction() ) + ".log";
    QFile logfile( path.c_str() );
    if ( logfile.exists() )
    {
        logfile.remove();
    }
    QCOMPARE( logfile.exists(), false );

    //@@@ TODO
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/*!
*/
QList<QString> DebugStreamTest::fileContents( const QString& path ) const
{
    QList<QString> ret = {};

    QFile file( path );
    if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QTextStream ts( &file );
        while ( !ts.atEnd() )
        {
            auto&& line = ts.readLine();
            ret.append( line );
        }
    }

    return ret;
}

QTEST_APPLESS_MAIN(DebugStreamTest)

#include "tst_debugstreamtest.moc"
