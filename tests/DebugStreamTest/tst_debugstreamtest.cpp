#include <QString>
#include <QtTest>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <QThread>
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
  @brief  endlマニピュレーターテスト
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
  @brief  timestampマニピュレーターテスト
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

    auto&& stream = izm::dbg::DebugStream( path );
    for ( int i = 0; i < 3; ++i )
    {
        stream << i << izm::timestamp << izm::endl;
        QThread::msleep( 1000 );  // 1000 msecs
    }

    QCOMPARE( logfile.exists(), true );

    auto&& contents = fileContents( logfile.fileName() );
    QCOMPARE( contents.size(), 3 );
}
//==============================================================================
/*!
  @brief  callerInfoマニピュレーターテスト
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

    auto&& stream = izm::dbg::DebugStream( path );
    stream << CALLERINFO << izm::endl;
    stream << CALLERINFO_L << izm::endl;

    QCOMPARE( logfile.exists(), true );

    auto&& contents = fileContents( logfile.fileName() );
    QCOMPARE( contents.size(), 2 );
    QCOMPARE( contents.at(0).contains( QTest::currentTestFunction() ), true );
    QCOMPARE( contents.at(1).contains( QTest::currentTestFunction() ), true );
}
//==============================================================================
/*!
  @brief  printfマニピュレーターテスト
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

    auto&& stream = izm::dbg::DebugStream( path );
    for ( int i = 0; i < 32; ++i )
    {
        stream << izm::printf( "%02d 0x%04X", i, i ) << izm::endl;
    }
    QCOMPARE( logfile.exists(), true );

    auto&& contents = fileContents( logfile.fileName() );
    QCOMPARE( contents.size(), 32 );
    QCOMPARE( contents.at(0), QString("00 0x0000") );
    QCOMPARE( contents.at(1), QString("01 0x0001") );
    QCOMPARE( contents.at(2), QString("02 0x0002") );
    QCOMPARE( contents.at(31), QString("31 0x001F") );
}
//==============================================================================
/*!
  @brief  everyマニピュレーターテスト
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

    auto&& stream = izm::dbg::DebugStream( path );
    for ( int i = 0; i < 64; ++i )
    {
        stream << izm::every(4) << i << izm::endl;
    }
    QCOMPARE( logfile.exists(), true );

    auto&& contents = fileContents( logfile.fileName() );
    QCOMPARE( contents.size(), 16 );
    QCOMPARE( contents.at(0), "0" );
    QCOMPARE( contents.at(1), "4" );
    QCOMPARE( contents.at(2), "8" );
    QCOMPARE( contents.at(3), "12" );
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
            auto&& line = ts.readLine().trimmed();
            ret.append( line );
        }
    }
    return ret;
}

QTEST_APPLESS_MAIN(DebugStreamTest)

#include "tst_debugstreamtest.moc"
