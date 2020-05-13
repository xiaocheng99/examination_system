#include "studydlg.h"
#include "ui_studydlg.h"
#include "choosesubdlg.h"
#include "questions.h"
#include "qdebug.h"

StudyDlg::StudyDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudyDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("学习界面");
    this->setAttribute(Qt::WA_DeleteOnClose);
    qDebug()<<listQueDone.count();
}

StudyDlg::~StudyDlg()
{
    delete ui;
}
void StudyDlg::InitListWidget(int ListIndex,QList<QStringList>List)//初始化表格函数
{
    ui->listwidgetQues->clear();
    ui->listwidgetQues->setSelectionMode(QAbstractItemView::SingleSelection);//设置智能单select
    for (int i=0;i<5;i++)
    {
        item =new QListWidgetItem;
        item->setText(List.at(ListIndex).at(i));
        if(i==0)
            item->setFlags(Qt::ItemIsEnabled);
        else
        {
            item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            item->setCheckState(Qt::Unchecked);
        }
        ui->listwidgetQues->addItem(item);
    }
    ui->EditCorret->setPlainText(labestr+StudyList.at(0).at(StudyList.at(0).at(5).toInt()));
    QString serInd= QString::asprintf("第%d题/共%d题",ListIndex+1,StudyList.count());
    ui->labeIndex->setText(serInd);


}

void StudyDlg::on_btnBack_clicked()
{
    this->close();
    ChooseSubDlg *choose=new ChooseSubDlg;
    choose->show();
}



void StudyDlg::on_btnNext_clicked()
{
    //点击进入下一题
    qDebug()<<ListIndex;
    //如果当前处于最后一题 那么下一题的按钮就会消失
    if(ListIndex==StudyList.count()-2)
    {
        ui->btnNext->setVisible(false);
    }

    isrecord=true;//进入第一步步将isrecord设置成true


    if(BtnLastTimes-1>=0)
    {

        isrecord=false;
        BtnLastTimes-=1;
    }
    //如果isrecord是true就进行记录
    ListIndex+=1;
    InitListWidget(ListIndex,StudyList);
    qDebug()<<"下一题："<<"做过的题数"<<listQueDone.count()<<"返回的次数"<<BtnLastTimes<<"当前的题号"<<listQueDone.count()-BtnLastTimes;
    qDebug()<<ListIndex;
    int correctIndex=StudyList.at(ListIndex).at(5).toInt();
    ui->EditCorret->setPlainText(labestr+StudyList.at(ListIndex).at(correctIndex));//获取下一题的答案写到text中


    //显示当前题号
    QString serInd= QString::asprintf("第%d题/共30题",ListIndex+1);
    ui->labeIndex->setText(serInd);
}

void StudyDlg::on_btnLast_clicked()
{
    //点击进入上一题

    ui->btnNext->setVisible(true);//如果从最后一题点击上一题就要先把下一题的按钮设置为可见的

    //如果当前处于第一题 上一题按钮的功能就消失掉
    if(ListIndex==0)
        return;
    BtnLastTimes+=1;//每点击一次进行累加
    ListIndex-=1;
    InitListWidget(ListIndex,StudyList);
    ui->EditCorret->setVisible(true);
    int correctIndex=StudyList.at(ListIndex).at(5).toInt();
    qDebug()<<"上一题："<<"做过的题数"<<listQueDone.count()<<"返回的次数"<<BtnLastTimes<<"当前的题号"<<listQueDone.count()-BtnLastTimes;
    ui->EditCorret->setPlainText(labestr+StudyList.at(ListIndex).at(correctIndex));//获取上一题的答案写到text中
    //显示当前题号
    QString serInd= QString::asprintf("第%d题/共30题",ListIndex+1);
    ui->labeIndex->setText(serInd);
}
