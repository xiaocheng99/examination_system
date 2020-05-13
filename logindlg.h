#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = nullptr);
    ~LoginDlg();
    QString m_user="user";//初始化用户名
    QString m_pswd="12345";//初始化密码 未加密的
    void readSettings();//读取设置 注册表
    void writeSettings();//写入设置 注册表
    QString encrpty(const QString& str);//字符串加密

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
