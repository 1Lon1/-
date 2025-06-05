#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>
#include <QDebug>

class Database
{
public:
    static Database& instance() {
        static Database db;
        return db;
    }

    bool connect(const QString& dbName = "server.db") {
        QMutexLocker locker(&mutex);
        if(db.isOpen()) return true;
        
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);
        
        if(!db.open()) {
            qCritical() << "Database error:" << db.lastError().text();
            return false;
        }
        
        createTables();
        return true;
    }

    QSqlQuery exec(const QString& query) {
        QMutexLocker locker(&mutex);
        return QSqlQuery(db);
    }

private:
    Database() = default;
    ~Database() {
        if(db.isOpen()) db.close();
    }

    void createTables() {
        exec("CREATE TABLE IF NOT EXISTS users ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
             "login TEXT UNIQUE NOT NULL, "
             "password TEXT NOT NULL)");
    }

    QSqlDatabase db;
    QMutex mutex;
};

#endif // DATABASE_H