/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/freechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file(":/source/style.css");
    file.open(QFile::ReadOnly);
    app.setStyleSheet(file.readAll());

    // ui
    Freechat window;
    window.show();

    return app.exec();
}
