#include "connectwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    // w.show();

    ConnectWidget cw;
    cw.show();

    return a.exec();
}
