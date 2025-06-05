#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>

MyTcpServer::~MyTcpServer()
{
    foreach(auto client, clients) {
        client->close();
        client->deleteLater();
    }
    mTcpServer->close();
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    Database::instance().connect();
    
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server error:" << mTcpServer->errorString();
    } else {
        qDebug() << "Server started on port 33333";
    }
}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket *clientSocket = mTcpServer->nextPendingConnection();
    qintptr id = clientSocket->socketDescriptor();
    clients[id] = clientSocket;
    
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    
    qDebug() << "New client connected:" << id;
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;
    
    QByteArray data = clientSocket->readAll();
    QByteArray response = ServerFunctions::parseRequest(data);
    clientSocket->write(response);
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if(!clientSocket) return;
    
    qintptr id = clientSocket->socketDescriptor();
    clients.remove(id);
    clientSocket->deleteLater();
    
    qDebug() << "Client disconnected:" << id;
}