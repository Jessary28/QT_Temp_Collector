#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Faradyne Motors - Epoxy Cure Temp Analysis");
    w.setFixedSize(1300,750);
    w.show();

    return a.exec();
}
