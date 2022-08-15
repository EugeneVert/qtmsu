#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addCheckmarks();

    ui->klistwidgetsearchline->setListWidget(ui->listWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCheckmarks()
{
    for (int i = 0; i < ui->listWidget->count(); i++) {
        auto *item = ui->listWidget->item(i);
        item->setCheckState(Qt::Unchecked);
    }
}
