/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include "Bin/bin.h"
#include "ui_freechat.h"
#include <QTextTableFormat>
#include <QMessageBox>
#include <QtWidgets>
#include <QDialog>

using namespace Qt;

class Freechat : public QDialog, private Ui::Freechat
{
    Q_OBJECT

private:
    QString ipOfPeer;
    QString nickNameOfPeer;
    QString yourIp;
    bool *replyForCD = nullptr; //not sure

public:
    Freechat(QWidget *parent = nullptr);
    ~Freechat();

private:
    void AskForConnectingToPortPeer();
    void AskForDisconnectingFromPortPeer();
    bool ReplyFromPortPeer(bool &reply);

private slots:
    void on_showNetworkInfo_clicked(bool checked);
    void on_connectionToPeer_clicked(bool checked);
    void on_writeNickOfPeer_textChanged(const QString &arg1);
    void on_writeLanIpOfPeer_textChanged(const QString &arg1);
    void on_writeWanIpOfPeer_textChanged(const QString &arg1);
};
#endif
