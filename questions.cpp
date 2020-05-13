#include "questions.h"
#include "QtDebug"
#include <QFile>
#include <QString>
#include <QStringList>
#include <ctime>
#include <cstdlib>
Questions::Questions()
{

EngSortlist();
ChSortlist();
MathSortlist();
}



void Questions::EngSortlist()
{
    int EngCount=0;
    QString path = ":/new/res/English.txt";//指定英语题目文件

    QString strline;//获取单行文本
    QFile file(path);

    file.open(QIODevice::ReadOnly);//只读的方式打开
    QTextStream stream(&file);//用文本流读取文件
stream.setAutoDetectUnicode(true);//自动监测unicode 读取文字时不会乱码
    txtStrList =new QStringList;
    while (!stream.atEnd())
    {
        strline=stream.readLine();//单行读取
        txtStrList->append(strline);//获取文件所有行数据
    }
    line=txtStrList->count();//获得题目总行数
    Num=line/6;//计算题目个数

//将每个题目为单位存储到容器中
    for(int i=0;i<Num;i++)
    {
         EngStrList.clear();//先清空缓存
        while(EngCount<line)
        {


           EngStrList<<txtStrList->at(EngCount);
            EngCount=EngCount+1;

            if(EngCount%6==0)//每六行跳出循环
                break;
        }
        EngList<<EngStrList;//一题一题保存题目
    }
    

//qDebug()<<EngList.at(1)<<EngList.count();//测试代码
file.close();
}
void Questions::ChSortlist()
{
    int EngCount=0;
    QString path = ":/new/res/Chinese.txt";//指定英语题目文件

    QString strline;//获取单行文本
    QFile file(path);
    file.open(QIODevice::ReadOnly);//只读的方式打开
    QTextStream stream(&file);//用文本流读取文件
 stream.setCodec("UTF-8");//自动监测unicode 读取文字时不会乱码
    txtStrList =new QStringList;
    while (!stream.atEnd())
    {
        strline=stream.readLine();//单行读取
        txtStrList->append(strline);//获取文件所有行数据
    }
    line=txtStrList->count();//获得题目总行数
    Num=line/6;//计算题目个数

//将每个题目为单位存储到容器中
    for(int i=0;i<Num;i++)
    {
         ChStrList.clear();//先清空缓存
        while(EngCount<line)
        {


           ChStrList<<txtStrList->at(EngCount);
            EngCount=EngCount+1;

            if(EngCount%6==0)//每六行跳出循环
                break;
        }
        ChList<<ChStrList;//一题一题保存题目
    }


qDebug()<<ChList.at(1).at(1)<<ChList.count();//测试代码
file.close();
}
 void Questions::MathSortlist()
 {
     int EngCount=0;
     QString path = ":/new/res/Math.txt";//指定英语题目文件

     QString strline;//获取单行文本
     QFile file(path);
     file.open(QIODevice::ReadOnly);//只读的方式打开
     QTextStream stream(&file);//用文本流读取文件
  stream.setCodec("UTF-8");//自动监测unicode 读取文字时不会乱码
     txtStrList =new QStringList;
     while (!stream.atEnd())
     {
         strline=stream.readLine();//单行读取
         txtStrList->append(strline);//获取文件所有行数据
     }
     line=txtStrList->count();//获得题目总行数
     Num=line/6;//计算题目个数

 //将每个题目为单位存储到容器中
     for(int i=0;i<Num;i++)
     {
          MathStrList.clear();//先清空缓存
         while(EngCount<line)
         {


            MathStrList<<txtStrList->at(EngCount);
             EngCount=EngCount+1;

             if(EngCount%6==0)//每六行跳出循环
                 break;
         }
         MathList<<MathStrList;//一题一题保存题目
     }


 qDebug()<<MathList.at(1)<<MathList.count();//测试代码
 file.close();
 }



