#ifndef STUDYDLG_H
#define STUDYDLG_H

#include <QDialog>
#include "questions.h"
#include"QListWidgetItem"
#include "QMessageBox"

namespace Ui {
class StudyDlg;
}

class StudyDlg : public QDialog
{
    Q_OBJECT

public:
    explicit StudyDlg(QWidget *parent = nullptr);
    ~StudyDlg();
    QList<QStringList>StudyList;//存放学习题目的容器
    Questions *question;//创建题目库对象
    QListWidgetItem *item;//listWidget的item
    int ListIndex=0;//list容器序列
    void InitListWidget(int ListIndex,QList<QStringList>List);//对Studylistwidget做初始化
    QString labestr="正确答案：";
    QList<int>listQueDone; //记录选择过得每一道题目的选项顺序
    bool isrecord=true;//判断是否能够记录所选题目的顺序
    int BtnLastTimes=0;//记录上一题按钮点击的次数

private slots:
    void on_btnBack_clicked();



    void on_btnNext_clicked();

    void on_btnLast_clicked();

private:
    Ui::StudyDlg *ui;
};

#endif // STUDYDLG_H
