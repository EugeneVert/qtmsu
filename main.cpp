#include "mainwindow.h"
#include "tmsumanage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s [file_name]", argv[0]);
        return 1;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
