#ifndef QUESTIONS_H
#define QUESTIONS_H
#include "QStringList"


class Questions
{
public:
    Questions();
    int line;//英语题目文档的行数
    int Num ;//英语题目的个数
    QStringList *txtStrList;//文本所有行数据

    QStringList EngStrList;//单个题目的数据
    QList<QStringList>EngList;//题目集合的数据 一个题目为一个单位

    QStringList ChStrList;//单个题目的数据
    QList<QStringList>ChList;//题目集合的数据 一个题目为一个单位

    QStringList MathStrList;//单个题目的数据
    QList<QStringList>MathList;//题目集合的数据 一个题目为一个单位
   //将文件的题目存放到list容器
    void EngSortlist();
    void ChSortlist();
    void MathSortlist();



};


#endif // QUESTIONS_H
