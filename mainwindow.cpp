#include "mainwindow.h"
#include "tmsumanage.h"
#include "ui_mainwindow.h"

#include <KListWidgetSearchLine>
#include <QCompleter>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList arguments = QCoreApplication::arguments();
    tmsu = new TmsuManage(arguments.mid(1, arguments.length()));
    addTags(tmsu->dbTags, tmsu->itemsTags, arguments.size() - 1);

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

void MainWindow::addTags(QStringList &dbTags, QMap<QString, uint> &itemTags, uint argsLen)
{
    uint count;
    for (const QString &i : dbTags) {
        QListWidgetItem *item = new QListWidgetItem(i);
        count = itemTags.value(i, 0);
        if (count == 0) {
            item->setCheckState(Qt::Unchecked);
        } else if (count == argsLen) {
            item->setCheckState(Qt::Checked);
        } else {
            item->setCheckState(Qt::PartiallyChecked);
        }
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_klistwidgetsearchline_returnPressed()
{
    if (ui->klistwidgetsearchline->text() == "") {
        return;
    }

    const auto foundItems = ui->listWidget->findItems(ui->klistwidgetsearchline->text(),
                                                      Qt::MatchFixedString);
    if (!foundItems.empty()) {
        if (QListWidgetItem *item = foundItems.at(0)) {
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

    QListWidgetItem *item = new QListWidgetItem(ui->klistwidgetsearchline->text());
    item->setCheckState(Qt::Checked);
    ui->listWidget->addItem(item);
    ui->klistwidgetsearchline->clear();
}

void MainWindow::on_applyButton_clicked()
{
    QStringList checked;
    QStringList unchecked;
    QListWidgetItem *item;
    Qt::CheckState state;
    uint statei;
    for (int i = 0; i < ui->listWidget->count(); i++) {
        item = ui->listWidget->item(i);
        state = item->checkState();
        if (state == Qt::Checked) {
            checked << item->text();
        } else if (state == Qt::Unchecked) {
            unchecked << item->text();
        }
    }
    tmsu->UpdateTags(checked, unchecked);
}
