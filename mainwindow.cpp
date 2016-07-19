#include <QtGui>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTreeWidget>
#include <QWidget>
#include <QStackedLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QMouseEvent>

#include "mainwindow.h"
#include "logindialog.h"
#include "SmtpClient/SmtpMime"
#include "Imap/imapmailbox.h"
#include "Imap/imapmessage.h"
#include "Imap/imapaddress.h"
#include "Imap/imap.h"
#include "SmtpClient/quotedprintable.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    writeEmailButton = new QPushButton(tr("Write Email"));
    receivedEmailButton = new QPushButton(tr("Received Email"));
    helpButton = new QPushButton(tr("Help"));


    QVBoxLayout *leftBottomLayout = new QVBoxLayout;
    leftBottomLayout->addWidget(writeEmailButton);
    leftBottomLayout->addWidget(receivedEmailButton);
    leftBottomLayout->addWidget(helpButton);
    leftBottomLayout->addStretch();

    userLab = new QLabel(tr("User: "));
    userNameLab = new QLabel(tr(""));
    userLab->setBuddy(userNameLab);
    logoutButton = new QPushButton(tr("Logout"));
    connect(logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    QVBoxLayout *leftTopLayout = new QVBoxLayout;
    leftTopLayout->addWidget(userLab);
    leftTopLayout->addWidget(userNameLab);
    leftTopLayout->addWidget(logoutButton);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    QWidget *leftBottomWidget = new QWidget;
    leftBottomWidget->setLayout(leftBottomLayout);
    QWidget *leftTopWidget = new QWidget;
    leftTopWidget->setLayout(leftTopLayout);
    leftLayout->addWidget(leftTopWidget);
    leftLayout->addWidget(leftBottomWidget);


    stackedLayout = new QStackedLayout();
    // send email content
    QWidget *sendEmailWidget = new QWidget;

    senderLab = new QLabel(tr("Sender:"));
    senderEdit = new QLineEdit();
    senderLab->setBuddy(senderEdit);
    receiverLab = new QLabel(tr("Receiver:"));
    receiverEdit = new QLineEdit();
    receiverLab->setBuddy(receiverEdit);
    subjectLab = new QLabel(tr("Subject"));
    subjectEdit = new QLineEdit();
    subjectLab->setBuddy(subjectEdit);
    contentLabel = new QLabel(tr("Content:"));
    contentEdit = new QTextEdit();
    contentLabel->setBuddy(contentEdit);
    sendEmailButton = new QPushButton(tr("Send Email"));
    connect(sendEmailButton, SIGNAL(clicked()), this, SLOT(writeEmail()));

    QGridLayout *sendEmailLayout = new QGridLayout;
    sendEmailLayout->addWidget(senderLab, 0, 0);
    sendEmailLayout->addWidget(senderEdit, 0, 1);
    sendEmailLayout->addWidget(receiverLab, 1, 0);
    sendEmailLayout->addWidget(receiverEdit, 1, 1);
    sendEmailLayout->addWidget(subjectLab, 2, 0);
    sendEmailLayout->addWidget(subjectEdit, 2, 1);
    sendEmailLayout->addWidget(contentLabel, 3, 0);
    sendEmailLayout->addWidget(contentEdit, 3, 1);
    sendEmailLayout->addWidget(sendEmailButton, 4, 0);

    sendEmailWidget->setLayout(sendEmailLayout);
    stackedLayout->addWidget(sendEmailWidget);

    // received email content
    QWidget *recEmailWidget = new QWidget;
    //QVBoxLayout *recEmailLayout = new QVBoxLayout;

    recEmailLabels = new QStringList();
    recEmailLabels->append(tr("ID"));
    recEmailLabels->append(tr("Sender"));
    recEmailLabels->append(tr("Subject"));
    recEmailTreeWidget = new QTreeWidget;
    recEmailTreeWidget->setHeaderLabels(*recEmailLabels);
    //recEmailLayout->addWidget(recEmailTreeWidget);
    connect(recEmailTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(viewEmail(QTreeWidgetItem*, int)));

    QGridLayout *viewEmailLayout = new QGridLayout;

    senderLab2 = new QLabel(tr("Sender:"));
    senderEdit2 = new QLineEdit();
    senderLab2->setBuddy(senderEdit2);
    receiverLab2 = new QLabel(tr("Receiver:"));
    receiverEdit2 = new QLineEdit();
    receiverLab2->setBuddy(receiverEdit2);
    subjectLab2 = new QLabel(tr("Subject"));
    subjectEdit2 = new QLineEdit();
    subjectLab2->setBuddy(subjectEdit2);
    contentLabel2 = new QLabel(tr("Content:"));
    contentEdit2 = new QTextEdit();
    contentLabel2->setBuddy(contentEdit2);
    viewEmailLayout->addWidget(senderLab2, 0, 0);
    viewEmailLayout->addWidget(senderEdit2, 0, 1);
    viewEmailLayout->addWidget(receiverLab2, 1, 0);
    viewEmailLayout->addWidget(receiverEdit2, 1, 1);
    viewEmailLayout->addWidget(subjectLab2, 2, 0);
    viewEmailLayout->addWidget(subjectEdit2, 2, 1);
    viewEmailLayout->addWidget(contentLabel2, 3, 0);
    viewEmailLayout->addWidget(contentEdit2, 3, 1);
    QPushButton *preEmailBtn = new QPushButton(tr("Previous Email"));
    QPushButton *nextEmailBtn = new QPushButton(tr("Next Email"));
    connect(preEmailBtn, SIGNAL(clicked()), this, SLOT(preEmail()));
    connect(nextEmailBtn, SIGNAL(clicked()), this, SLOT(nextEmail()));
    viewEmailLayout->addWidget(preEmailBtn, 4, 0);
    viewEmailLayout->addWidget(nextEmailBtn, 4, 1);
    QWidget *viewEmailWidget = new QWidget;
    viewEmailWidget->setLayout(viewEmailLayout);

    recEmailStackedLayout = new QStackedLayout;
    recEmailStackedLayout->addWidget(recEmailTreeWidget);
    recEmailStackedLayout->addWidget(viewEmailWidget);

    //recEmailWidget->setLayout(recEmailLayout);
    recEmailWidget->setLayout(recEmailStackedLayout);
    stackedLayout->addWidget(recEmailWidget);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addLayout(stackedLayout);

    QHBoxLayout *mailLayout = new QHBoxLayout;
    mailLayout->addLayout(leftLayout);
    mailLayout->addLayout(rightLayout);
    QWidget *mailWidget = new QWidget();
    mailWidget->setLayout(mailLayout);

    recGesWidget = new RecGestureWidget(this);
    QHBoxLayout *recGesLayout = new QHBoxLayout;
    recGesResultLab = new QLabel(tr("None"));
    recGesLayout->addWidget(recGesResultLab);
    recGesWidget->setLayout(recGesLayout);

    QImage img(QString(tr("HelpPic.png")));
    img = img.scaled(1280, 720);
    QWidget *helpWidget = new QWidget;
    QLabel *helpLab = new QLabel;
    helpLab->setPixmap(QPixmap::fromImage(img));
    QHBoxLayout *helpLayout = new QHBoxLayout;
    helpLayout->addWidget(helpLab);
    helpWidget->setLayout(helpLayout);
    stackedLayout->addWidget(helpWidget);

    mainStaLayout = new QStackedLayout();
    mainStaLayout->setStackingMode(QStackedLayout::StackOne);
    mainStaLayout->addWidget(mailWidget);
    mainStaLayout->addWidget(recGesWidget);

    QWidget *mainWidget = new QWidget();
    mainWidget->setLayout(mainStaLayout);
    this->setCentralWidget(mainWidget);

    recGesWidget->mySet(mainStaLayout);


    connect(writeEmailButton, SIGNAL(clicked()), this, SLOT(switchLayout()));
    connect(receivedEmailButton, SIGNAL(clicked()), this, SLOT(switchLayout()));
    connect(helpButton, SIGNAL(clicked()), this, SLOT(switchLayout()));

    this->curViewWmailId = -1;
    this->b_login = false;
    this->login();
}

void MainWindow::switchLayout()
{
    QPushButton *pbtn = dynamic_cast<QPushButton*>(this->sender());
    if (pbtn == writeEmailButton)
    {
        stackedLayout->setCurrentIndex(0);
    }
    else if (pbtn == receivedEmailButton)
    {
        stackedLayout->setCurrentIndex(1);
        recEmailStackedLayout->setCurrentIndex(0);
        receiveEmail();
    }
    else
    {
        stackedLayout->setCurrentIndex(2);
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{

}


void MainWindow::login()
{
    LoginDialog *dialog = new LoginDialog(this);
    if (dialog->exec())
    {
        QString tmp = dialog->user;
        user = dialog->user;
        password = dialog->password;
        user = QString(tr("13968062190@163.com"));
        password = QString(tr("agxpvlfztcbqnrxc"));
        SmtpClient smtp("smtp.163.com", 465, SmtpClient::SslConnection);
        smtp.setUser(user);
        smtp.setPassword(password);
        smtp.connectToHost();
        if (smtp.login() == true)
        {
            QMessageBox::information(this, tr(""), tr("Login Succeed"), QMessageBox::Yes);
            this->userNameLab->setText(user);
            this->b_login = true;
            logoutButton->setText(tr("Logout"));
        }
        else
        {
            QMessageBox::warning(this, tr("Warning!"), tr("Login Failed"), QMessageBox::Yes);
            this->b_login = false;
            logoutButton->setText(tr("Login"));
        }

        smtp.quit();
    }
    else
    {
        QMessageBox::warning(this, tr("Quit"), tr("Quit"), QMessageBox::Yes);
        this->b_login = false;
        logoutButton->setText(tr("Login"));
    }

    delete dialog;
}

void MainWindow::logout()
{
    this->m_Email.clear();
    while (recEmailTreeWidget->topLevelItemCount() > 0)
    {
        delete recEmailTreeWidget->topLevelItem(0);
    }
    userNameLab->clear();
    stackedLayout->setCurrentIndex(0);
    senderEdit->clear();
    receiverEdit->clear();
    subjectEdit->clear();
    contentEdit->clear();

    this->b_login = false;
    logoutButton->setText(tr("Login"));

    this->login();
}

void MainWindow::writeEmailWindow()
{
    senderLab = new QLabel(tr("Sender:"));
    senderEdit = new QLineEdit();
    senderLab->setBuddy(senderEdit);
    receiverLab = new QLabel(tr("Receiver:"));
    receiverEdit = new QLineEdit();
    receiverLab->setBuddy(receiverEdit);
    subjectLab = new QLabel(tr("Subject"));
    subjectEdit = new QLineEdit();
    subjectLab->setBuddy(subjectEdit);
    contentLabel = new QLabel(tr("Content:"));
    contentEdit = new QTextEdit();
    contentLabel->setBuddy(contentEdit);

    sendEmailButton = new QPushButton(tr("Send Email"));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        mainStaLayout->setStackingMode(QStackedLayout::StackAll);
        mainStaLayout->setCurrentIndex(1);
        mainStaLayout->widget(1)->setFocus(Qt::MouseFocusReason);
        mainStaLayout->widget(1)->grabMouse();
    }
}

void MainWindow::curRecognizedGes(QString str)
{
    this->recGesResultLab->setText(str);
}

void MainWindow::writeEmail()
{
    if (this->b_login == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Please login first!"), QMessageBox::Yes);
        return ;
    }
    if (stackedLayout->currentIndex() != 0)
    {
         return ;
    }
    if (senderEdit->text().isEmpty() == true)
    {
        QMessageBox::warning(this, tr("Warning!"), tr("Sender is empty!"), QMessageBox::Yes);
        return ;
    }
    if (receiverEdit->text().isEmpty() == true)
    {
        QMessageBox::warning(this, tr("Warning!"), tr("Receiver is empty!"), QMessageBox::Yes);
        return ;
    }
    if (subjectEdit->text().isEmpty() == true)
    {
        QMessageBox::warning(this, tr("Warning"), tr("Subject is empty!"), QMessageBox::Yes);
        return ;
    }
    if (contentEdit->toPlainText().isEmpty() == true)
    {
        QMessageBox::warning(this, tr("Warning!"), tr("Content is empty!"), QMessageBox::Yes);
    }
    SmtpClient smtp("smtp.163.com", 465, SmtpClient::SslConnection);
    smtp.setUser(user);
    smtp.setPassword(password);
    qDebug()<<user<<password;
    MimeMessage message;
    message.setSender(new EmailAddress(senderEdit->text(), senderEdit->text()));
    message.addRecipient(new EmailAddress(receiverEdit->text(), receiverEdit->text()));
    message.setSubject(subjectEdit->text());

    MimeText text;
    text.setText(contentEdit->toPlainText());
    message.addPart(&text);

    //message.addPart(new MimeAttachment(new QFile("")));

    bool result=false;
    result = smtp.connectToHost();
    if (result == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Connect to host failed!"), QMessageBox::Yes);
        return;
    }
    result = smtp.login();
    if (result == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Login failed!"), QMessageBox::Yes);
        return;
    }
    result = smtp.sendMail(message);
    if (result == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Send mail failed!"), QMessageBox::Yes);
        return;
    }
    smtp.quit();

    QMessageBox::information(this, tr(""), tr("Send mail succeed"), QMessageBox::Yes);
}

bool MainWindow::receiveEmail()
{
    if (this->b_login == false)
    {
        QMessageBox::critical(this, tr("Error!"), tr("Please login first!"), QMessageBox::Yes);
        return false;
    }

    stackedLayout->setCurrentIndex(1);
    recEmailStackedLayout->setCurrentIndex(0);

    this->m_Email.clear();
    while (recEmailTreeWidget->topLevelItemCount() > 0)
    {
        delete recEmailTreeWidget->topLevelItem(0);
    }

    Imap imap;
    if (!imap.connectToHost("imap.163.com", 993, true))
    {
        QMessageBox::critical(this, tr("Error"), tr("Connect to host failed!"), QMessageBox::Yes);
        return false;
    }
    if (!imap.login(user, password, Imap::LoginPlain))
    {
        QMessageBox::critical(this, tr("Error"), tr("Login failed!"), QMessageBox::Yes);
        return false;
    }

    ImapMailbox *mailbox = imap.select("INBOX");
    QList<int> messageList,m1,m2,m3,m4,m5,m6,m7;
    m1 = imap.searchUnseen();
    m2 = imap.searchRecent();
    m3 = imap.searchAnswered();
    m4 = imap.searchDraft();
    m5 = imap.searchDeleted();
    m6 = imap.searchUnanswered();
    m7 = imap.searchRecentUnseen();
    qDebug()<<m1<<"--"<<m2<<"--"<<m3<<"--"<<m4<<"--"<<m5<<"--"<<m6<<"--"<<m7;

    messageList = m1+m2+m3+m4+m5+m6+m7;

    // Delete duplicate mails
    for (int i=0;i<messageList.size();i++)
    {
         for (int j=messageList.size()-1;j>i;j--)
         {
             if (messageList[j] == messageList[i])
             {
                 messageList.removeAt(j);
             }
         }
    }

    if (imap.fetch(mailbox, messageList) == NULL)
    {
        QMessageBox::critical(this, tr("Error"), tr("Fetch failed!"), QMessageBox::Yes);
        return false;
    }
    foreach (int msgId, messageList)
    {
       ImapMessage *message = mailbox->findById(msgId);
       if (message == NULL)
       {
           //qDebug() << "Message" << msgId << "Not Found.";
           continue;
       }
       if (!imap.fetchBodyStructure(message))
       {
           QMessageBox::critical(this, tr("Error"), tr("FetchBodyStructure failed!"), QMessageBox::Yes);
       }
       QDateTime sentTime = message->sent();
       QDateTime receivedTime = message->received();


       EmailInfo emailInfo;
       emailInfo.id = msgId;
       emailInfo.sender = message->fromAddress().toString();
       emailInfo.receiver = message->toAddresses().at(0).toString();
       emailInfo.subject = message->subject();

       QStringList mailInfo;
       mailInfo<<QString::number(msgId)<<message->fromAddress().toString()<<message->subject();

       QTreeWidgetItem *item = new QTreeWidgetItem(recEmailTreeWidget, mailInfo);
       for (int i = 0; i < message->bodyPartCount(); ++i)
       {
           ImapMessageBodyPart *bodyPart = message->bodyPartAt(i);

           if (!imap.fetchBodyPart(message, i))
           {
               QMessageBox::critical(this, tr("Error"), tr("FetchBodyPart failed!"), QMessageBox::Yes);
           }
           emailInfo.content += QuotedPrintable::decode(bodyPart->data());
           //qDebug()<<bodyPart->contentType()<<bodyPart->encoding();
       }
       this->m_Email.push_back(emailInfo);
    }

    delete mailbox;
    imap.logout();
    imap.disconnectFromHost();

    return true;
}

void MainWindow::viewEmail(QTreeWidgetItem* item, int column)
{
    if (this->b_login == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Please login first!"), QMessageBox::Yes);
        return ;
    }
    QString idStr = item->text(0);
    this->curViewWmailId = idStr.toInt()-1;

    recEmailStackedLayout->setCurrentIndex(1);
    senderEdit2->setText(this->m_Email[this->curViewWmailId].sender);
    receiverEdit2->setText(this->m_Email[this->curViewWmailId].receiver);
    subjectEdit2->setText(this->m_Email[this->curViewWmailId].subject);
    contentEdit2->setHtml(this->m_Email[this->curViewWmailId].content);
}

void MainWindow::nextEmail()
{
    if (this->b_login == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Please login first!"), QMessageBox::Yes);
        return ;
    }
    this->curViewWmailId++;
    if (this->curViewWmailId == 0)
    {
        if (receiveEmail() == false)
        {
            return ;
        }
    }
    if (this->curViewWmailId >= (int)this->m_Email.size())
    {
        this->curViewWmailId = this->m_Email.size()-1;
    }

    stackedLayout->setCurrentIndex(1);
    recEmailStackedLayout->setCurrentIndex(1);

    senderEdit2->setText(this->m_Email[this->curViewWmailId].sender);
    receiverEdit2->setText(this->m_Email[this->curViewWmailId].receiver);
    subjectEdit2->setText(this->m_Email[this->curViewWmailId].subject);
    contentEdit2->setHtml(this->m_Email[this->curViewWmailId].content);
    qDebug()<<this->m_Email[this->curViewWmailId].content;
}

void MainWindow::preEmail()
{
    if (this->b_login == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Please login first!"), QMessageBox::Yes);
        return ;
    }
     this->curViewWmailId--;
     if (this->curViewWmailId <= 0)
     {
         this->curViewWmailId = 0;
     }
     if (this->curViewWmailId == 0)
     {
          if (receiveEmail() == false)
          {
               return ;
          }
     }
     stackedLayout->setCurrentIndex(1);
     recEmailStackedLayout->setCurrentIndex(1);

    senderEdit2->setText(this->m_Email[this->curViewWmailId].sender);
    receiverEdit2->setText(this->m_Email[this->curViewWmailId].receiver);
    subjectEdit2->setText(this->m_Email[this->curViewWmailId].subject);
    contentEdit2->setHtml(this->m_Email[this->curViewWmailId].content);
}

void MainWindow::deleteEmail()
{
    if (this->b_login == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Please login first!"), QMessageBox::Yes);
        return ;
    }
    if (this->curViewWmailId<0 || this->curViewWmailId>=(int)this->m_Email.size())
    {
        return ;
    }
    if (stackedLayout->currentIndex() == 0)
    {
         return ;
    }
    if (recEmailStackedLayout->currentIndex() == 0)
    {
        return ;
    }

    while (recEmailTreeWidget->topLevelItemCount() > 0)
    {
        delete recEmailTreeWidget->topLevelItem(0);
    }

    Imap imap;
    if (!imap.connectToHost("imap.163.com", 993, true))
    {
        QMessageBox::critical(this, tr("Error"), tr("Connect to host failed!"), QMessageBox::Yes);
        return ;
    }
    if (!imap.login(user, password, Imap::LoginPlain))
    {
        QMessageBox::critical(this, tr("Error"), tr("Login failed!"), QMessageBox::Yes);
        return ;
    }

    ImapMailbox *mailbox = imap.select("INBOX");
    QList<int> messageList,m1,m2,m3,m4,m5,m6,m7;
    m1 = imap.searchUnseen();
    m2 = imap.searchRecent();
    m3 = imap.searchAnswered();
    m4 = imap.searchDraft();
    m5 = imap.searchDeleted();
    m6 = imap.searchUnanswered();
    m7 = imap.searchRecentUnseen();

    messageList = m1+m2+m3+m4+m5+m6+m7;

    if (imap.fetch(mailbox, messageList) == NULL)
    {
        QMessageBox::critical(this, tr("Error"), tr("Fetch failed!"), QMessageBox::Yes);
        return ;
    }

    bool result = imap.setDeleted(this->curViewWmailId+1, true);
    if (result == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Delete mail failed!"), QMessageBox::Yes);
        return ;
    }

    vector<EmailInfo>::iterator itr = this->m_Email.begin()+this->curViewWmailId;
    this->m_Email.erase(itr);
    this->curViewWmailId++;
    if (this->curViewWmailId >= (int)this->m_Email.size())
    {
         this->curViewWmailId = this->m_Email.size()-1;
    }

    delete mailbox;
    imap.logout();
    imap.disconnectFromHost();
}
