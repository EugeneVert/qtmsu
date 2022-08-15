#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KListWidgetSearchLine>
#include <QMainWindow>

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

    void addCheckmarks();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
