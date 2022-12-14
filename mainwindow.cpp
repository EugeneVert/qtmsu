#include "mainwindow.h"
#include "tmsumanage.h"
#include "ui_mainwindow.h"

#include <KListWidgetSearchLine>
#include <QCompleter>
#include <QKeyEvent>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->installEventFilter(this);

    QStringList arguments = QCoreApplication::arguments();
    tmsu = new TmsuManage(arguments.mid(1, arguments.length()));
    addTags(tmsu->dbTags, tmsu->itemsTags, arguments.size() - 1);

    comp = new QCompleter(tmsu->dbTags, this);
    comp->setCompletionMode(QCompleter::PopupCompletion);

    ui->klistwidgetsearchline->setListWidget(ui->listWidget);
    ui->klistwidgetsearchline->installEventFilter(this);
    installCompleter();

    QShortcut *shortcut = new QShortcut(QKeySequence(tr("Alt+Shift+A", "Show only active")), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::on_showOnlyActive);
    on_showOnlyActive();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tmsu;
    delete comp;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (obj == ui->centralwidget) {
            if (Qt::Key_Escape == keyEvent->key()) {
                close();
            }
        } else if (obj == ui->klistwidgetsearchline) {
            if (Qt::Key_Return == keyEvent->key()) {
                if (Qt::Modifier::CTRL == keyEvent->modifiers()
                    | Qt::Modifier::SHIFT == keyEvent->modifiers()) {
                    on_applyButton_clicked();
                    close();
                }
                on_klistwidgetsearchline_returnPressed();
            }
        }
    }

    return false;
}

void MainWindow::on_showOnlyActive()
{
    showOnlyActive = !showOnlyActive;
    updateListWidgetActive();
}

void MainWindow::updateListWidgetActive()
{
    for (int i = 0; i < ui->listWidget->count(); i++) {
        auto *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::CheckState::Unchecked) {
            if (showOnlyActive) {
                item->setHidden(true);
            } else {
                item->setHidden(false);
            }
        }
    }
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
    if (ui->klistwidgetsearchline->text().isEmpty()) {
        return;
    }

    const auto foundItems = ui->listWidget->findItems(ui->klistwidgetsearchline->text(),
                                                      Qt::MatchFixedString);
    if (!foundItems.empty()) {
        if (QListWidgetItem *item = foundItems.at(0)) {
            if (item->checkState() != Qt::Checked) {
                item->setCheckState(Qt::Checked);
            } else {
                item->setCheckState(Qt::Unchecked);
            }
        }
    } else {
        QListWidgetItem *item = new QListWidgetItem(ui->klistwidgetsearchline->text());
        item->setCheckState(Qt::Checked);
        ui->listWidget->addItem(item);
    }

    ui->klistwidgetsearchline->updateSearch("");
    ui->klistwidgetsearchline->selectAll();
    updateListWidgetActive();
    updateCompleter();
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

void MainWindow::installCompleter()
{
    compEnabled = true;
    ui->klistwidgetsearchline->setCompleter(comp);
}

void MainWindow::removeCompleter()
{
    compEnabled = false;
    ui->klistwidgetsearchline->setCompleter(nullptr);
}

void MainWindow::updateCompleter()
{
    if (compEnabled) {
        ui->klistwidgetsearchline->setCompleter(comp);
    } else {
        ui->klistwidgetsearchline->setCompleter(nullptr);
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == 0) {
        removeCompleter();
    } else {
        installCompleter();
    }
}

void MainWindow::on_klistwidgetsearchline_textChanged(const QString &arg1)
{
    if (!compEnabled) {
        return;
    }
    uint len = arg1.length();
    if (arg1.endsWith("=")) {
        preArgumentLen = len - 1;
        const QString &mid = arg1.mid(0, preArgumentLen);
        QStringList values = tmsu->GetTagValues(mid);
        for (auto &i : values) {
            i = arg1 + i;
        }
        argumentComp = new QCompleter(values);
        ui->klistwidgetsearchline->setCompleter(argumentComp);
    }
    if (preArgumentLen != 0 && len < preArgumentLen) {
        ui->klistwidgetsearchline->setCompleter(comp);
    }
}
