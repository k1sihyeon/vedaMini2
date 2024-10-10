#include "widget.h"
#include "loginwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    LoginWidget lw;
    lw.show();

    return a.exec();
}
