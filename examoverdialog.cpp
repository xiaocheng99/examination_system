#include "examoverdialog.h"
#include "ui_examoverdialog.h"
#include <qdebug.h>
#include "examwindow.h"
#include "mainwindow.h"

ExamOverDialog::ExamOverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExamOverDialog)
{
    ui->setupUi(this);
this->setWindowTitle("成绩界面");
this->setAttribute(Qt::WA_DeleteOnClose);
}

ExamOverDialog::~ExamOverDialog()
{
    delete ui;
}



void ExamOverDialog::on_btnExamGo_clicked()
{
    this->close();
    ExamWindow *examwindow=new ExamWindow;
    examwindow->show();
}

void ExamOverDialog::on_btnBackExam_clicked()
{
    this->close();
}

void ExamOverDialog::on_btnBack_clicked()
{
    this->close();
    MainWindow *mainwindow=new MainWindow;
    mainwindow->show();
}
