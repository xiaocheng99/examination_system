#ifndef EXAMOVERDIALOG_H
#define EXAMOVERDIALOG_H

#include <QDialog>
#include "QPlainTextEdit"

namespace Ui {
class ExamOverDialog;
}

class ExamOverDialog : public QDialog
{
    Q_OBJECT

public:
      Ui::ExamOverDialog *ui;
    explicit ExamOverDialog(QWidget *parent = nullptr);
    ~ExamOverDialog();

    QString Subject;//薄弱学科
    int ExamResult=0;//考试成绩
    //记录每个学科的错误次数 初始化为0
    int ChErrorNum=0;
    int EngErrorNum=0;
    int MathErrorNum=0;
  QPlainTextEdit edit;


private slots:


  void on_btnExamGo_clicked();

  void on_btnBackExam_clicked();

  void on_btnBack_clicked();

private:

};

#endif // EXAMOVERDIALOG_H
