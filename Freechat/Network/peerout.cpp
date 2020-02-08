/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerout.h"

Peerout::Peerout()
    : nextBlockSize(0)
{
    socket = new QTcpSocket(this);

    #ifndef Q_DEBUG
    qDebug() << "A new socket created.";
    #endif

    connect(socket, SIGNAL(connected()), this, SLOT(SlotConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(SlotReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(SlotError(QAbstractSocket::SocketError)));
}

Peerout::~Peerout()
{
    delete socket;
}

void Peerout::SlotReadyRead()
{
    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_4_2);
    QString buffer;

    #ifndef Q_DEBUG
    qDebug() << "Read data from server";
    #endif

    for(;;)
    {
        if(!nextBlockSize)
        {
            if(socket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            stream >> nextBlockSize;
        }

        if(socket->bytesAvailable() < nextBlockSize)
        {
            break;
        }

        QTime time = QTime::currentTime();
        QString message;
        stream >> message;

        #ifndef Q_DEBUG
        qDebug() << "Data from server: " << message;
        #endif

        Freechat::viewField->append(time.toString() + ":" + "Peer: " + message + "\n");
        nextBlockSize = 0;
    }

    return;
}

void Peerout::SlotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found.\n" :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed.\n" :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused.\n" :
                         QString(socket->errorString()));

    // show error in view field
    Freechat::viewField->append(strError);

    return;
}

void Peerout::SlotSendToServer()
{
    #ifndef Q_DEBUG
    qDebug() << "Sending data to server from peerout.cpp: " << Freechat::bufferOfMessages;
    #endif

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream.setVersion(QDataStream::Qt_4_2);
    sendStream << quint16(0) << Freechat::bufferOfMessages;

    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));
    socket->write(block);

    Freechat::bufferOfMessages.clear();

    return;
}

void Peerout::SlotConnecting()
{
    #ifndef Q_DEBUG
    qDebug() << "Connecting to " << Freechat::lanIpOfPeer;
    #endif

    QHostAddress hostAddress(Freechat::lanIpOfPeer);
    socket->connectToHost(hostAddress, 6000);

    if(socket->waitForConnected(2000))
    {
        #ifndef Q_DEBUG
        qDebug() << "Connected.";
        #endif
    }
    else
    {
        #ifndef Q_DEBUG
        qDebug() << "Error connection.";
        #endif
    }

    Freechat::lanIpOfPeer.clear();

    return;
}

void Peerout::SlotConnected()
{
    Freechat::viewField->append("Connected to peerin\n");

    #ifndef Q_DEBUG
    qDebug() << "Connected.";
    #endif

    return;
}
