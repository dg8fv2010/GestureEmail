#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    userLab = new QLabel(tr("User Name: "));
    userEdit = new QLineEdit();
    userLab->setBuddy(userEdit);

    passwordLab = new QLabel(tr("Password: "));
    passwordEdit = new QLineEdit();
    passwordLab->setBuddy(passwordEdit);

    okBtn = new QPushButton(tr("OK"));
    cancelBtn = new QPushButton(tr("Cancel"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(userLab);
    topLayout->addWidget(userEdit);
    QWidget *topWidget = new QWidget;
    topWidget->setLayout(topLayout);
    QHBoxLayout *midLayout = new QHBoxLayout;
    midLayout->addWidget(passwordLab);
    midLayout->addWidget(passwordEdit);
    QWidget *midWidget = new QWidget;
    midWidget->setLayout(midLayout);
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(okBtn);
    bottomLayout->addWidget(cancelBtn);
    bottomLayout->addStretch();
    QWidget *bottomWidget = new QWidget;
    bottomWidget->setLayout(bottomLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topWidget);
    layout->addWidget(midWidget);
    layout->addWidget(bottomWidget);
    setLayout(layout);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(okBtn, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));

}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::okClicked()
{
    this->user = userEdit->text();
    this->password = passwordEdit->text();
    //qDebug() << this->user << this->password;
}

void LoginDialog::cancelClicked()
{
    this->close();
    //emit cancelClickedSig();
}

