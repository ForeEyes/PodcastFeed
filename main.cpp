#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Set Fixed Window Size
    w.setFixedSize(900,530);
    //Set Window Title
    w.setWindowTitle("Podcast Feed");
    w.show();

    return a.exec();
}
