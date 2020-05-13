#ifndef CHOOSESUBDLG_H
#define CHOOSESUBDLG_H

#include <QDialog>

namespace Ui {
class ChooseSubDlg;
}

class ChooseSubDlg : public QDialog
{
    Q_OBJECT

public:
     Ui::ChooseSubDlg *ui;
    explicit ChooseSubDlg(QWidget *parent = nullptr);
    ~ChooseSubDlg();

private slots:
    void on_btnBack_clicked();

    void on_btnChinese_clicked();

    void on_btnMath_clicked();

    void on_btnEnglish_clicked();

private:

};

#endif // CHOOSESUBDLG_H
