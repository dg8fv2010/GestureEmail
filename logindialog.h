#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent=0);
    ~LoginDialog();

signals:

private slots:
    void okClicked();
    void cancelClicked();

public:
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *userLab;
    QLineEdit *userEdit;
    QLabel *passwordLab;
    QLineEdit *passwordEdit;


    QString user;
    QString password;

};

#endif
