#include "choosesubdlg.h"
#include "ui_choosesubdlg.h"
#include "mainwindow.h"
#include "studydlg.h"
#include "studydlg.h"

ChooseSubDlg::ChooseSubDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseSubDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("选择科目界面");
    this->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口时释放内存
}

ChooseSubDlg::~ChooseSubDlg()
{
    delete ui;
}

void ChooseSubDlg::on_btnBack_clicked()
{
    this->close();
    MainWindow *mainwindow=new MainWindow;
    mainwindow->show();
}

void ChooseSubDlg::on_btnChinese_clicked()
{
    this->close();
    StudyDlg *Chinese=new StudyDlg;
    Chinese->question=new Questions;//创建一个题库对象
    //将题库的科目分别随机排序
    srand(static_cast<unsigned int>(time(0)));//设置随机种子 作用是让每次打开软件随机后的顺序都都不一样
    //将题库全部打乱
    std::random_shuffle(Chinese->question->ChList.begin(),Chinese->question->ChList.end());
    Chinese->StudyList=Chinese->question->ChList;
    Chinese->show();
    Chinese-> InitListWidget(Chinese-> ListIndex,Chinese->StudyList);

}

void ChooseSubDlg::on_btnMath_clicked()
{
    this->close();
    StudyDlg *Math=new StudyDlg;

    Math->question=new Questions;//创建一个题库对象
    //将题库的科目分别随机排序
    srand(static_cast<unsigned int>(time(0)));//设置随机种子 作用是让每次打开软件随机后的顺序都都不一样
    //将题库全部打乱
    std::random_shuffle(Math->question->MathList.begin(),Math->question->MathList.end());
    Math->StudyList=Math->question->MathList;
    Math->show();
    Math-> InitListWidget(Math-> ListIndex,Math->StudyList);
    Math->show();
}

void ChooseSubDlg::on_btnEnglish_clicked()
{
    this->close();
    StudyDlg *English=new StudyDlg;
    English->question=new Questions;//创建一个题库对象
    //将题库的科目分别随机排序
    srand(static_cast<unsigned int>(time(0)));//设置随机种子 作用是让每次打开软件随机后的顺序都都不一样
    //将题库全部打乱
    std::random_shuffle(English->question->EngList.begin(),English->question->EngList.end());
    English->StudyList=English->question->EngList;
    English->show();
    English-> InitListWidget(English-> ListIndex,English->StudyList);
    English->show();
}
