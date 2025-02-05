#ifndef ASKPENDINGMANAGER_H
#define ASKPENDINGMANAGER_H

#include <QObject>

#include <sqlite/sqlite_types.h>

#include <util/classhelpers.h>
#include <util/ioc/iocservice.h>

class LogEntryConn;

class AskPendingManager : public QObject, public IocService
{
    Q_OBJECT

public:
    explicit AskPendingManager(QObject *parent = nullptr);
    CLASS_DELETE_COPY_MOVE(AskPendingManager)

    SqliteDb *sqliteDb() const { return m_sqliteDb.data(); }

    void setUp() override;

    void logConn(const LogEntryConn &entry);

private:
    bool setupDb();

private:
    SqliteDbPtr m_sqliteDb;
};

#endif // ASKPENDINGMANAGER_H
