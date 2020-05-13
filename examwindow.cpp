#include "examwindow.h"
#include "ui_examwindow.h"
#include "mainwindow.h"
#include <QtDebug>
#include"questions.h"
#include<QAbstractItemView>
#include <QMessageBox>
#include <QString>
#include "examoverdialog.h"
#include "examoverdialog.h"
#include "ui_examoverdialog.h"
#include<QFile>
#include <QByteArray>
#include <QSettings>


ExamWindow::ExamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExamWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("考试界面");
    ChangSubNum( ChNum,EngNum,MathNum);
    qDebug()<<ChNum<<EngNum<<MathNum;
    question=new Questions;//创建一个题库对象
    //将题库的科目分别随机排序
    srand(static_cast<unsigned int>(time(0)));//设置随机种子 作用是让每次打开软件随机后的顺序都都不一样
    //将语数英题库全部打乱
    std::random_shuffle(question->MathList.begin(),question->MathList.end());
    std::random_shuffle(question->EngList.begin(),question->EngList.end());
    std::random_shuffle(question->ChList.begin(),question->ChList.end());
    sortExamList();//打乱后的题库整合成考试题库
    qDebug()<<"随机后"<<ExamList;//
    //初始化表格
    InitListWidget(ListIndex,ExamList);


}

ExamWindow::~ExamWindow()
{
    delete  question;
    delete  item;
    delete ui;
}

void ExamWindow::on_btnBack_clicked()
{

    this->hide();
    MainWindow *main=new MainWindow;
    main->show();

}
void ExamWindow::InitListWidget(int ListIndex,QList<QStringList>List)//初始化表格函数
{
    ui->listExam->clear();
    ui->listExam->setSelectionMode(QAbstractItemView::SingleSelection);//设置智能单select
    //
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
        ui->listExam->addItem(item);

    }
    ui->TextCorrect->setText(labestr+ExamList.at(0).at(5));
    ui->TextCorrect->setVisible(false);
    //初始化当前题号
    QString serInd= QString::asprintf("第%d题/共30题",ListIndex+1);
    ui->labIndex->setText(serInd);


}



void ExamWindow::on_listExam_itemSelectionChanged()
{
    //选择事件

    //设置单选
    int row=ui->listExam->currentRow();//获得当前行数
    bool a=ui->TextCorrect->isVisible();//判断是否已经答过题
    //当所选的项为0或者已经答题 当前选项禁选
    if(row==0||a)
        return;

    //将所有的选项变为uncheked
    for (int i=1;i<5;i++)
    {

        ui->listExam->item(i)->setCheckState(Qt::Unchecked);
    }
    //将当前的item设置为checked
    if(ui->listExam->item(row)->isSelected())
        ui->listExam->item(row)->setCheckState(Qt::Checked);
}

void ExamWindow::on_btnNext_clicked()
{
    //点击进入下一题
    qDebug()<<ListIndex;
    //如果当前处于最后一题 那么下一题的按钮就会消失
    if(ListIndex==28)
    {
        ui->btnNext->setVisible(false);
    }

    isrecord=true;//进入第一步步将isrecord设置成true

    //如果当没有选择题目就进行下一题时 跳出对话框进行询问
    if((ui->listExam->currentRow()==-1||ui->listExam->currentRow()==0)&&BtnLastTimes==0)
    {
        QMessageBox::about(this,"空","请选择一个选项！");
        return;
    }
    if(BtnLastTimes-1>=0)
    {

        isrecord=false;
        BtnLastTimes-=1;
    }
    //如果isrecord是true就进行记录
    if((isrecord||result==QMessageBox::Yes)&&SubDone)
    {
        for (int i=1;i<5;i++)
        {
            if(ui->listExam->item(i)->checkState())
                listQueDone<<i;
        }
        qDebug()<<listQueDone;
    }

    ListIndex+=1;
    InitListWidget(ListIndex,ExamList);
    qDebug()<<"下一题："<<"做过的题数"<<listQueDone.count()<<"返回的次数"<<BtnLastTimes<<"当前的题号"<<listQueDone.count()-BtnLastTimes;

    if(BtnLastTimes>0)
    {
        ui->TextCorrect->setVisible(true);
        qDebug()<<ListIndex;
        int correctIndex=ExamList.at(ListIndex).at(5).toInt();
        ui->TextCorrect->setText(labestr+ExamList.at(listQueDone.count()-BtnLastTimes).at(correctIndex));//获取上下题的答案写到text中
        ui->listExam->item(listQueDone.at(listQueDone.count()-BtnLastTimes))->setSelected(true);//将之前所选的答案选中
        ui->listExam->item(listQueDone.at(listQueDone.count()-BtnLastTimes))->setCheckState(Qt::Checked);

    }
    //显示当前题号
    QString serInd= QString::asprintf("第%d题/共30题",ListIndex+1);
    ui->labIndex->setText(serInd);

}

void ExamWindow::on_btnLast_clicked()
{
    //点击进入上一题

    ui->btnNext->setVisible(true);//如果从最后一题点击上一题就要先把下一题的按钮设置为可见的

    //如果当前处于第一题 上一题按钮的功能就消失掉
    if(ListIndex==0)
        return;
    BtnLastTimes+=1;//每点击一次进行累加
    isrecord=false;
    ListIndex-=1;
    InitListWidget(ListIndex,ExamList);
    ui->TextCorrect->setVisible(true);
    int correctIndex=ExamList.at(ListIndex).at(5).toInt();
    qDebug()<<"上一题："<<"做过的题数"<<listQueDone.count()<<"返回的次数"<<BtnLastTimes<<"当前的题号"<<listQueDone.count()-BtnLastTimes;
    ui->TextCorrect->setText(labestr+ExamList.at(listQueDone.count()-BtnLastTimes).at(correctIndex));//获取上一题的答案写到text中

    ui->listExam->item(listQueDone.at(listQueDone.count()-BtnLastTimes))->setSelected(true);//将之前所选的答案选中
    ui->listExam->item(listQueDone.at(listQueDone.count()-BtnLastTimes))->setCheckState(Qt::Checked);

    //显示当前题号
    QString serInd= QString::asprintf("第%d题/共30题",ListIndex+1);
    ui->labIndex->setText(serInd);
}

void ExamWindow::on_btnConfirm_clicked()
{     //点击确认按钮

    //已经确认过题程序直接退出 不作判断
    if(ui->TextCorrect->isVisible())
    {
        QMessageBox::about(this,"error","您已经答过题，无需重复确认");

        return;
    }


    int row=ui->listExam->currentRow();//获取当前所选的行

    //    isrecord=false;//将其设置为false 后面点下一题的时候就不会再记录一次
    //    listQueDone<<row;//直接将当前选项录入
    //    qDebug()<<listQueDone;//测试

    qDebug()<<row<<ListIndex<<question->EngList.at(ListIndex);//测试
    int correctIndex=ExamList.at(ListIndex).at(5).toInt();//将答案的那一行转成整型数字
    //当所选为空时获得row为-1
    if(row==-1||row==0)
    {
        QMessageBox::about(this,"空","回答为空,请选择一个选项");
    }
    //当所选行等于正确答案行 提示回答正确
    if(row==correctIndex)
    {
        ui->TextCorrect->setVisible(true);//将答案框显示出来
        ui->TextCorrect->setText(labestr+ExamList.at(ListIndex).at(correctIndex));//设置答案内容
        QMessageBox::about(this,"正确","回答正确");//跳出提示框

    }
    //当所选行不是正确答案且不为空时  提示回答错误
    if(row!=correctIndex&&row!=-1&&row!=0)
    {
        ui->TextCorrect->setVisible(true);
        ui->TextCorrect->setText(labestr+ExamList.at(ListIndex).at(correctIndex));
        QMessageBox::about(this,"错误","回答错误");
    }

}

void ExamWindow::sortExamList()
{
    //创建ExamList题库
    for (int i=0;i<ChNum;i++)
    {
        ExamList<<question->ChList.at(i);
    }
    for (int i=0;i<EngNum;i++)
    {
        ExamList<<question->EngList.at(i);
    }
    for (int i=0;i<MathNum;i++)
    {
        ExamList<<question->MathList.at(i);
    }
}



void ExamWindow::on_btnSubmit_clicked()
{
    ExamOverDialog *overDlg=new ExamOverDialog(this);
    //监听信号 如果答题界面点击了继续考试 那么此窗口就需要关闭
    connect(overDlg->ui->btnExamGo,&QPushButton::clicked,this,&ExamWindow::close);
    connect(overDlg->ui->btnBack,&QPushButton::clicked,this,&ExamWindow::close);
    qDebug()<<"提交后："<<ListIndex;
    int row=ui->listExam->currentRow();//获取当前所选的行

    //如果已经交卷了 再次点击就进入成绩查看界面
    if(!SubDone)
    {
        //点击查看成绩之后显示成绩
        InitOverWin(overDlg);
        //打开成绩窗口
        overDlg->exec();
    }

    if(ListIndex==29&&SubDone)
    {
        //当所选为空时获得row为-1或0时 表示最后一题未答题
        if(row==-1||row==0)
        {
            QMessageBox::about(this,"空","回答为空,请选择一个选项");
            return;
        }

        result= QMessageBox::question(this,"注意！","是否确定交卷？",
                                      QMessageBox::Yes|QMessageBox::No);

        //当接收的按钮是NO 程序结束
        if(result==QMessageBox::No)
        {
            qDebug()<<"no";
            return;
        }
        //当接收的按钮是Yes 程序继续执行
        if(result==QMessageBox::Yes)
        {
            //如果SubDone是true就进行记录
            if(SubDone)
            {
                for (int i=1;i<5;i++)
                {
                    if(ui->listExam->item(i)->checkState())
                        listQueDone<<i;
                }
                qDebug()<<listQueDone;
                InitOverWin(overDlg);//点击确认之后显示成绩
                SubDone=false;//将SubDone设置为fale代表已经提交过题目了 下一次就不会再执行 避免重复记录listDone
                ui->btnSubmit->setText("查看成绩");//当已经提交过题目后 第二次按钮就变成"查看成绩"
                BtnLastTimes+=1;//当已经点击过提交题目后 将记录返回的变量加1 如果不这样返回查看试卷的时候最后一题显示没有做过
            }
            overDlg->exec();//以模态窗口的形式打开
            qDebug()<<"yes";
        }

    }


}
void ExamWindow::InitOverWin(ExamOverDialog *overDlg)
{

    for(int i=0;i<ChNum;i++)
    {
        if(listQueDone.at(i)==ExamList.at(i).at(5).toInt())
        {
            overDlg->ExamResult+=4;
        }
        if(listQueDone.at(i)!=ExamList.at(i).at(5).toInt())
        {
            overDlg->ChErrorNum+=1;
        }
    }
    for(int i=ChNum;i<EngNum+ChNum;i++)
    {
        if(listQueDone.at(i)==ExamList.at(i).at(5).toInt())
        {
            overDlg->ExamResult+=4;
        }
        if(listQueDone.at(i)!=ExamList.at(i).at(5).toInt())
        {
            overDlg->EngErrorNum+=1;
        }
    }
    for(int i=EngNum+ChNum;i<EngNum+ChNum+MathNum;i++)
    {
        if(listQueDone.at(i)==ExamList.at(i).at(5).toInt())
        {
            overDlg->ExamResult+=4;
        }
        if(listQueDone.at(i)!=ExamList.at(i).at(5).toInt())
        {
            overDlg->MathErrorNum+=1;
        }
    }
    //判断哪一科错的题目较多
    Recommend(overDlg);

    //在成绩界面上显示当前成绩
    qDebug()<<overDlg->ExamResult;
    QString str=QString::asprintf("%d",overDlg->ExamResult);
    overDlg->ui->LabelResult->setText(str);
}
void ExamWindow::Recommend(ExamOverDialog *overDlg)
{
    //实现推荐算法
    //将错题的科目用数字记录在注册表中 0均匀 1语文 2英语 3数学 以便于下次打开软件可以读取
    QSettings settinges("Qt","AnswerQuestions");
    if((overDlg->ChErrorNum==overDlg->EngErrorNum)||(overDlg->ChErrorNum==overDlg->MathErrorNum)||(overDlg->EngErrorNum==overDlg->MathErrorNum))
    {
        if((overDlg->ChErrorNum==overDlg->MathErrorNum)>overDlg->EngErrorNum)
        {
            overDlg->ui->labelSubject->setText("当前错题较多的科目为:语文和数学");
            settinges.setValue("subject","012");
        }
        if(overDlg->EngErrorNum>(overDlg->ChErrorNum==overDlg->MathErrorNum))
        {
            overDlg->ui->labelSubject->setText("当前错题较多的科目为:英语");
            settinges.setValue("subject","3");
        }
        if((overDlg->ChErrorNum==overDlg->EngErrorNum)>overDlg->MathErrorNum)
        {
            overDlg->ui->labelSubject->setText("当前错题较多的科目为:语文和英语");
            settinges.setValue("subject","013");
        }
        if(overDlg->MathErrorNum>(overDlg->ChErrorNum==overDlg->EngErrorNum))
        {
            overDlg->ui->labelSubject->setText("当前错题较多的科目为:数学");
            settinges.setValue("subject","2");
        }
        if((overDlg->EngErrorNum==overDlg->MathErrorNum)>overDlg->ChErrorNum)
        {
            overDlg->ui->labelSubject->setText("当前错题较多的科目为:英语和数学");
            settinges.setValue("subject","023");
        }
        if(overDlg->ChErrorNum>(overDlg->EngErrorNum==overDlg->MathErrorNum))
        {
            overDlg->ui->labelSubject->setText("当前错题较多的科目为:语文");
            settinges.setValue("subject","1");
        }
        if((overDlg->EngErrorNum==overDlg->MathErrorNum)==overDlg->ChErrorNum)
        {
            overDlg->ui->labelSubject->setText("当前错题较多的科目为:无");
            settinges.setValue("subject","0");
        }
    }
        //这里就是当没有错题数目相等的时候
        else
        {
            if(overDlg->ChErrorNum>overDlg->MathErrorNum>overDlg->EngErrorNum)
            {
                //语文 数学 英语
                overDlg->ui->labelSubject->setText("当前错题较多的科目为:语文和数学");
                settinges.setValue("subject","12");
            }
            if(overDlg->ChErrorNum>overDlg->EngErrorNum>overDlg->MathErrorNum)
            {
                //语文 英语 数学
                overDlg->ui->labelSubject->setText("当前错题较多的科目为:语文、英语");
                settinges.setValue("subject","13");
            }
            if(overDlg->MathErrorNum>overDlg->EngErrorNum>overDlg->ChErrorNum)
            {
                //数学 英语 语文
                overDlg->ui->labelSubject->setText("当前错题较多的科目为:数学、英语");
                settinges.setValue("subject","23");
            }
            if(overDlg->MathErrorNum>overDlg->ChErrorNum>overDlg->EngErrorNum)
            {
                //数学 语文 英语
                overDlg->ui->labelSubject->setText("当前错题较多的科目为:数学、语文");
                settinges.setValue("subject","21");
            }
            if(overDlg->EngErrorNum>overDlg->ChErrorNum>overDlg->MathErrorNum)
            {
                //英语 语文 数学
                overDlg->ui->labelSubject->setText("当前错题较多的科目为:英语、语文");
                settinges.setValue("subject","31");
            }
            if(overDlg->EngErrorNum>overDlg->MathErrorNum>overDlg->ChErrorNum)
            {
                //英语 数学 语文
                overDlg->ui->labelSubject->setText("当前错题较多的科目为:英语、数学");
                settinges.setValue("subject","32");
            }
        }


    qDebug()<<settinges.value("subject","0").toString();
}
void ExamWindow::ChangSubNum(int& Ch,int& Eng,int& Math)
{
    QSettings settinges("Qt","AnswerQuestions");
    int Num=settinges.value("subject","0").toInt();//读取注册表的值 没有值就读取缺省值
    qDebug()<<settinges.value("subject","0").toString();
    qDebug()<<Num;
    switch (Num)
    {
    case 0: break;
    case 1: Ch+=10;
        Eng-=5;
        Math-=5;
        break;
    case 2: Eng+=10;
        Ch-=5;
        Math-=5;
        break;
    case 3: Math+=10;
        Eng-=5;
        Ch-=5;
        break;
    case 12: Ch+=5;
        Eng-=5;

        break;
    case 13: Ch+=5;

        Math-=5;
        break;
    case 21: Math+=5;
        Eng-=5;

        break;
    case 23: Math+=5;

        Ch-=5;
        break;
    case 31: Eng+=5;
        Eng-=5;

        break;
    case 32: Eng+=5;

        Ch-=5;
        break;
    case 012: Ch+=2;
        Eng-=4;
        Math+=2;
        break;
    case 013: Ch+=2;
        Eng+=2;
        Math-=4;
        break;
    case 023: Ch-=4;
        Eng+=2;
        Math+=2;
        break;

    }


}
