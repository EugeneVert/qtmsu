#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QCompleter;
class TmsuManage;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    TmsuManage *tmsu;
    QCompleter *comp;
    void addTags(QStringList &dbTags, QMap<QString, uint> &itemTags, uint argsLen);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_klistwidgetsearchline_returnPressed();
    void on_applyButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
