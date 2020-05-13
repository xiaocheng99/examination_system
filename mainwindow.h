#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //初始化mainwindow
    void InitMain();
private slots:
    void on_btnExam_clicked();

    void on_btnResetSub_clicked();

    void on_btnStudy_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
