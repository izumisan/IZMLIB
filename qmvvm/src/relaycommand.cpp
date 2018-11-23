#include <cassert>
#include "relaycommand.h"

namespace izm
{
namespace qmvvm
{

RelayCommand::RelayCommand( QObject* parent,
              const std::function<void()>& execute )
    : ICommand( parent )
    , m_execute( execute )
{
    assert( m_execute != nullptr );
}

RelayCommand::RelayCommand( QObject* parent,
              const std::function<void()>& execute,
              const std::function<bool()>& canExecute )
    : ICommand( parent )
    , m_execute( execute )
    , m_canExecute( canExecute )
{
    assert( m_execute != nullptr );
    assert( m_canExecute != nullptr );
}

void RelayCommand::execute()
{
    m_execute();
}

bool RelayCommand::canExecute() const
{
    return m_canExecute();
}

void RelayCommand::raiseCanExecute() const
{
    Q_EMIT canExecuteChanged();
}

} // namespace qmvvm
} // namespace izm
