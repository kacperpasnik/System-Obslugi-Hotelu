#include "logowanie.h"
#include <QApplication>
#include "menuglowne.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logowanie w;
    w.show();


    return a.exec();
}
