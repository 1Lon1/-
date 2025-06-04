#include <QCoreApplication>
#include <mytcpserver.h>

int main(inc argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer myserv;
    return a.exec();
}