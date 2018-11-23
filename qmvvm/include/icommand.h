#ifndef IZM_QMVVM_ICOMMAND_H
#define IZM_QMVVM_ICOMMAND_H

#include <QObject>

namespace izm
{
namespace qmvvm
{

class ICommand : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool canExecute READ canExecute NOTIFY canExecuteChanged )
Q_SIGNALS:
    void canExecuteChanged() const;

public:
    explicit ICommand( QObject* parent = nullptr ) : QObject(parent) {}
    virtual ~ICommand() = default;

public:
    virtual void execute() = 0;
    virtual bool canExecute() const = 0;
    virtual void raiseCanExecute() const = 0;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_ICOMMAND_H
