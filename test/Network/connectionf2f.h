/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTIONF2F_H
#define CONNECTIONF2F_H

#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QNetworkSession>
#include <QHostAddress>
#include <QHostAddress>
#include <QTimerEvent>
#include <QTcpSocket>
#include <QHostInfo>
#include <QtNetwork>

class ConnectionF2F : public QTcpSocket
{
    Q_OBJECT

public:
    static QString globalNetworkBuffer;

public:
    ConnectionF2F(QObject *parent = nullptr);
    ~ConnectionF2F();

private:
    void OpenConnectingToPortPeer();
    void OpenDisconnectingFromPortPeer();
    void NetworkInfo();
};
#endif
