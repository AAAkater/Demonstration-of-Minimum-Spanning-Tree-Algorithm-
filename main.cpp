#include "Prim.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Prim w;
    w.show();
    return a.exec();
}
