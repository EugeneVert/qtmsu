#include "mainwindow.h"
#include "tmsumanage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s [file_names]", argv[0]);
        return 1;
    }
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon::fromTheme("folder-tag"));
    MainWindow w;
    w.show();
    return a.exec();
}
