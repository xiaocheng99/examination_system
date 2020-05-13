#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "examwindow.h"
#include "questions.h"
#include "QSettings"
#include "choosesubdlg.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitMain();
    this->setWindowTitle("自适应学习系统");

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::InitMain()
{
    QSettings settings("Qt","AnswerQuestions");
    int Num=settings.value("subject","0").toInt();
    switch (Num)
    {
    case 0: ui->labelSub->setText("无");
        break;
    case 1: ui->labelSub->setText("语文");
        break;
    case 2: ui->labelSub->setText("数学");
        break;
    case 3: ui->labelSub->setText("英语");
        break;
    case 12: ui->labelSub->setText("语文、数学");

        break;
    case 13: ui->labelSub->setText("语文、英语");
        break;
    case 21: ui->labelSub->setText("数学、语文");

        break;
    case 23:ui->labelSub->setText("数学、英语");
        break;
    case 31: ui->labelSub->setText("英语、语文");

        break;
    case 32: ui->labelSub->setText("英语、数学");
        break;
    case 012: ui->labelSub->setText("语文和数学");
        break;
    case 013: ui->labelSub->setText("语文和英语");
        break;
    case 023:ui->labelSub->setText("数学和英语");
        break;
    }
}

void MainWindow::on_btnExam_clicked()
{
    this->hide();
    ExamWindow *exam=new ExamWindow(this);
    exam->show();
}

void MainWindow::on_btnResetSub_clicked()
{
    QSettings settings("Qt","AnswerQuestions");
    settings.setValue("subject","0");
    ui->labelSub->setText("无");
}

void MainWindow::on_btnStudy_clicked()
{
    this->close();
    ChooseSubDlg *choose=new ChooseSubDlg;
    choose->show();
}
