#ifndef FUNCTIONSFORSERVER_H
#define FUNCTIONSFORSERVER_H

#include <QByteArray>
#include <QString>

namespace ServerFunctions {
    QByteArray parseRequest(const QByteArray& data);
    QByteArray authUser(const QString& login, const QString& pass);
    QByteArray registerUser(const QString& login, const QString& pass);
};

#endif // FUNCTIONSFORSERVER_H