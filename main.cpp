#include "mainwidget.h"
#include "types.h"

#include <QtWidgets/QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication aplication(argc, argv);
    MainWidget w;
    w.show();

    return aplication.exec();
}
