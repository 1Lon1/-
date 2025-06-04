#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObjext>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetworl>
#include <QByteArray>
#include <QDebug>

class MyTcpServer : public QObject
{
        Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
private:
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
};
#endif