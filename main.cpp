#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QFont>
#include <QPushButton>

using namespace Qt;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget Freechat;
    QPixmap pix("D:/Freechat/Freechat/Freechat/unnamed.png");
    QCursor cur(pix);

    QPushButton quit("Quit", &Freechat);
    quit.setFont(QFont("Terminal", 18, QFont::Bold));
    quit.setGeometry(10, 40, 180, 40);
    QObject::connect(&quit, SIGNAL(clicked()), &app, SLOT(quit()));

    Freechat.setCursor(cur);
    Freechat.resize(750, 550);
    Freechat.show();

    return app.exec();
}
