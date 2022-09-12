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
    QCompleter *argumentComp;
    bool compEnabled = false;
    bool showOnlyActive = false;
    uint preArgumentLen = 0;
    void addTags(QStringList &dbTags, QMap<QString, uint> &itemTags, uint argsLen);
    void installCompleter();
    void removeCompleter();
    void updateCompleter();
    void updateListWidgetActive();


protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_showOnlyActive();
    void on_klistwidgetsearchline_returnPressed();
    void on_applyButton_clicked();
    void on_checkBox_stateChanged(int arg1);

    void on_klistwidgetsearchline_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
