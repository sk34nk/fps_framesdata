#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication fps_framesdata(argc, argv);
    MainWindow w;
    w.show();

    return fps_framesdata.exec();
}
