#include <cassert>
#include <future>
#include "commandmanager.h"
#include "asynccommand.h"

namespace izm
{
namespace qmvvm
{

AsyncCommand::AsyncCommand( QObject* parent,
              const std::function<void()>& execute )
    : ICommand( parent )
    , m_execute( execute )
{
    assert( m_execute != nullptr );
}

AsyncCommand::AsyncCommand( QObject* parent,
              const std::function<void()>& execute,
              const std::function<bool()>& canExecute,
              const bool autoRaise )
    : ICommand( parent )
    , m_execute( execute )
    , m_canExecute( canExecute )
{
    assert( m_execute != nullptr );
    assert( m_canExecute != nullptr );

    if ( autoRaise )
    {
        connect( CommandManager::instance(),
                 &CommandManager::requerySuggested,
                 this,
                 [this] { raiseCanExecuteChanged(); },
                 Qt::QueuedConnection );

        CommandManager::instance()->start();
    }
}

void AsyncCommand::execute()
{
    m_task = std::async( std::launch::async, [this]{ m_execute(); } );
}

bool AsyncCommand::canExecute() const
{
    return m_canExecute();
}

void AsyncCommand::raiseCanExecuteChanged() const
{
    Q_EMIT canExecuteChanged();
}

} // namespace qmvvm
} // namespace izm
