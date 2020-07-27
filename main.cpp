#include "CrossPE.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CrossPE w;
    w.show();
    return a.exec();
}