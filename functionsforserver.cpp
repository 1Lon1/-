#include "functionsforserver.h"
#include "database.h"
#include <QDebug>

QByteArray ServerFunctions::parseRequest(const QByteArray& data)
{
    QString strData = QString::fromUtf8(data).trimmed();
    
    if(strData.startsWith("AUTH:")) {
        QStringList parts = strData.mid(5).split(":");
        if(parts.size() == 2) {
            return authUser(parts[0], parts[1]);
        }
    }
    else if(strData.startsWith("REG:")) {
        QStringList parts = strData.mid(4).split(":");
        if(parts.size() == 2) {
            return registerUser(parts[0], parts[1]);
        }
    }
    
    return "ERROR:UNKNOWN_COMMAND";
}

QByteArray ServerFunctions::authUser(const QString& login, const QString& pass)
{
    auto& db = Database::instance();
    QSqlQuery query = db.exec(
        QString("SELECT password FROM users WHERE login = '%1'").arg(login));
    
    if(query.next() && query.value(0).toString() == pass) {
        return "AUTH:OK";
    }
    return "AUTH:FAIL";
}

QByteArray ServerFunctions::registerUser(const QString& login, const QString& pass)
{
    auto& db = Database::instance();
    QSqlQuery check = db.exec(
        QString("SELECT id FROM users WHERE login = '%1'").arg(login));
    
    if(check.next()) {
        return "REG:EXISTS";
    }
    
    QSqlQuery query = db.exec(
        QString("INSERT INTO users (login, password) VALUES ('%1', '%2')")
        .arg(login).arg(pass));
    
    return query.lastError().isValid() ? "REG:FAIL" : "REG:OK";
}