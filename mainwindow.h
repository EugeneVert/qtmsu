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
    void addTags(QStringList &dbTags, QStringList &itemTags);
    TmsuManage *tmsu;
    QCompleter *comp;
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_klistwidgetsearchline_returnPressed();
    void on_applyButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
