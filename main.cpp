#include "mainwindow.h"

#include <QApplication>
#include<QTextCodec>
#include <logindlg.h>


int main(int argc, char *argv[])
{
    
    QApplication a(argc, argv);
    LoginDlg *login=new LoginDlg;
    if(login->exec()==QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
   else
        return  0;
}
