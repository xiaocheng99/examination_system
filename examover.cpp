#include "examover.h"
#include "ui_examover.h"

ExamOver::ExamOver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamOver)
{
    ui->setupUi(this);
}

ExamOver::~ExamOver()
{
    delete ui;
}
