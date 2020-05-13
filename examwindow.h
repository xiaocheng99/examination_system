#ifndef EXAMWINDOW_H
#define EXAMWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <questions.h>
#include <QMessageBox>
#include "examoverdialog.h"

namespace Ui {
class ExamWindow;
}

class ExamWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExamWindow(QWidget *parent = nullptr);
    ~ExamWindow();
    QList<QStringList>ExamList;//存放考试题目的容器
    Questions *question;
    QListWidgetItem *item;//listWidget的item
    int ListIndex=0;//list容器序列
    QMessageBox::StandardButton result;//接收button的类型
    void InitListWidget(int ListIndex,QList<QStringList>List);//对Examlistwidget做初始化
    QString labestr="正确答案：";
    QList<int>listQueDone; //记录选择过得每一道题目的选项顺序
    bool isrecord=true;//判断是否能够记录所选题目的顺序
    int BtnLastTimes=0;//记录上一题按钮点击的次数

    bool SubDone=true;//判断有没有点击过交卷
    //初始化题目数量
    int ChNum=10;
    int EngNum=10;
    int MathNum=10;
    void sortExamList();
    //对成绩界面框进行初始化
    void InitOverWin(ExamOverDialog *overDlg);
    //推荐算法（判断当前错题较多的科目）
    void Recommend(ExamOverDialog *overDlg);
    //实现将题目数量根据错题进行相应的更改
    void ChangSubNum(int& Ch,int&  Eng,int&  Math);



private slots:
    void on_btnBack_clicked();

    void on_listExam_itemSelectionChanged();

    void on_btnNext_clicked();

    void on_btnLast_clicked();

    void on_btnConfirm_clicked();



    void on_btnSubmit_clicked();

private:
    Ui::ExamWindow *ui;
};

#endif // EXAMWINDOW_H
