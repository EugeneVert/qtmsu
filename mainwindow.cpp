#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tmsumanage.h"

#include <KListWidgetSearchLine>
#include <QCompleter>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tmsu = new TmsuManage(QCoreApplication::arguments().at(1));
    addTags(tmsu->dbTags, tmsu->itemTags);

    comp = new QCompleter(tmsu->dbTags);
    comp->setCompletionMode(QCompleter::PopupCompletion);

    ui->klistwidgetsearchline->setListWidget(ui->listWidget);
    ui->klistwidgetsearchline->installEventFilter(this);
    ui->klistwidgetsearchline->setCompleter(comp);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tmsu;
    delete comp;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->klistwidgetsearchline && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (Qt::Key_Return == keyEvent->key()) {
            if (Qt::Modifier::CTRL == keyEvent->modifiers()) {
                on_applyButton_clicked();
                close();
            }
            on_klistwidgetsearchline_returnPressed();
        }
    }
    return false;
}

void MainWindow::addTags(QStringList &dbTags, QStringList &itemTags)
{
    for (const QString &i : dbTags) {
        QListWidgetItem *item = new QListWidgetItem(i);
        if (itemTags.contains(i)) {
            item->setCheckState(Qt::Checked);
        } else {
            item->setCheckState(Qt::Unchecked);
        }
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_klistwidgetsearchline_returnPressed()
{
    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (ui->klistwidgetsearchline->text() == item->text()) {
            if (item->checkState() == Qt::Unchecked) {
                item->setCheckState(Qt::Checked);
                ui->klistwidgetsearchline->clear();
                return;
            }
            item->setCheckState(Qt::Unchecked);
            ui->klistwidgetsearchline->clear();
            return;
        }
    }
    if (ui->klistwidgetsearchline->text() == "") {
        return;
    }
    QListWidgetItem *item = new QListWidgetItem(ui->klistwidgetsearchline->text());
    item->setCheckState(Qt::Checked);
    ui->listWidget->addItem(item);
    ui->klistwidgetsearchline->clear();
}

void MainWindow::on_applyButton_clicked()
{
    QStringList l;
    QListWidgetItem *item;
    for (int i = 0; i < ui->listWidget->count(); i++) {
        item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            l << item->text();
        }
    }
    tmsu->UpdateTags(l);
}
