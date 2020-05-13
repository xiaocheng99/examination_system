#include "logindlg.h"
#include "ui_logindlg.h"
#include <QSettings>
#include <QByteArray>
#include <QCryptographicHash>
#include <QMessageBox>

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("登陆界面");
    ui->EditPSWD->setEchoMode(QLineEdit::Password);//设置为密码模式
    this->setAttribute(Qt::WA_DeleteOnClose);//关闭时删除
    readSettings();//读取存储的用户名和密码
}

LoginDlg::~LoginDlg()
{
    delete ui;
}
void LoginDlg::readSettings()
{
    //读取存储的用户名和密码，密码是经过加密的
    QSettings settinges("Qt","AnswerQuestions");
   m_user=settinges.value("Username","user").toString();
   QString defaultPSWD=encrpty("12345");
   m_pswd=settinges.value("PSWD",defaultPSWD).toString();

}
void LoginDlg::writeSettings()
{
    //保存用户名
     QSettings settinges("Qt","AnswerQuestions");
     settinges.setValue("Username",m_user);
     settinges.setValue("PSWD",m_pswd);
}
QString LoginDlg::encrpty(const QString& str)
{
    QByteArray btArray;
    btArray.append(str);
    QCryptographicHash hash(QCryptographicHash::Md5);//MD5加密算法
    hash.addData(btArray);//添加数据
    QByteArray resultArray=hash.result();//返回最终的散列值
    QString md5=resultArray.toHex();//转成16进制字符串
    return  md5;

}

void LoginDlg::on_btnOk_clicked()
{
    //确定按钮
    QString user=ui->EditUser->text().trimmed();//输入用户名
    QString pswd=ui->EditPSWD->text().trimmed();//输入密码
    QString encryptPSWD=encrpty(pswd);//对输入的密码加密
    if((user==m_user)&&(encryptPSWD==m_pswd))
    {
        writeSettings();//将账户密码写入注册表
        this->accept();//对话框 accept 关闭对话框
    }
    else
        QMessageBox::warning(this,"错误提示","用户名或密码错误");
}

void LoginDlg::on_btnCancel_clicked()
{
    this->close();
}
