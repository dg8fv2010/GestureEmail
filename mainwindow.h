#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

#include <iostream>
#include <vector>

#include "recGestureWidget.h"

using namespace std;

class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;
class QListWidget;
class QTreeWidget;
class QStackedLayout;
class QHBoxLayout;
class QTreeWidget;
class QTreeWidgetItem;


struct EmailInfo
{
    int id;
    QString sender;
    QString receiver;
    QString sendDate;
    QString receiveDate;
    QString subject;
    QString content;
    QString mailType;
};

class MainWindow : public QMainWindow
//class MainWindow : public QDialog
{
    Q_OBJECT

public:
        MainWindow(QWidget *parent=0);
        ~MainWindow();

protected:
        void closeEvent(QCloseEvent *event);

private slots:
    void switchLayout();
    void logout();
    void writeEmail();
    bool receiveEmail();
    void viewEmail(QTreeWidgetItem*, int);
    void nextEmail();
    void preEmail();
    void deleteEmail();
    void curRecognizedGes(QString);


private:
    QPushButton *writeEmailButton;
    QPushButton *receivedEmailButton;


    void writeEmailWindow();
    void receivedEmailWindow();

    //void switchLayout();
    QStackedLayout *stackedLayout;

    QLabel *userLab;
    QLabel  *userNameLab;
    QPushButton *logoutButton;

    // helpwindow widget
    QPushButton *helpButton;

    // writeEmailWindow widget
    QLabel *senderLab;
    QLineEdit *senderEdit;
    QLabel *receiverLab;
    QLineEdit *receiverEdit;
    QLabel *subjectLab;
    QLineEdit *subjectEdit;
    QLabel *contentLabel;
    QTextEdit *contentEdit;
    QPushButton *sendEmailButton;

    // receivedEmailWindow widget
    QLabel *senderLab2;
    QLineEdit *senderEdit2;
    QLabel *receiverLab2;
    QLineEdit *receiverEdit2;
    QLabel *subjectLab2;
    QLineEdit *subjectEdit2;
    QLabel *contentLabel2;
    QTextEdit *contentEdit2;

    QStringList *recEmailLabels;
    QTreeWidget *recEmailTreeWidget;
    QTextEdit *recEmailEdit;
    QStackedLayout *recEmailStackedLayout;
    vector<EmailInfo> m_Email;
    int curViewWmailId;

    void mousePressEvent(QMouseEvent *event);
    QLabel *gestureLab;
    QStackedLayout *mainStaLayout;
    RecGestureWidget *recGesWidget;
    QLabel *recGesResultLab;

    QString user;
    QString password;

    void login();
    bool b_login;
};
#endif

