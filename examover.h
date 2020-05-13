#ifndef EXAMOVER_H
#define EXAMOVER_H

#include <QWidget>

namespace Ui {
class ExamOver;
}

class ExamOver : public QWidget
{
    Q_OBJECT

public:
    explicit ExamOver(QWidget *parent = nullptr);
    ~ExamOver();

private:
    Ui::ExamOver *ui;
};

#endif // EXAMOVER_H
