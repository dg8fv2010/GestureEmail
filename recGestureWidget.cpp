#include <QMouseEvent>
#include <QtGui>
#include <QMessageBox>
#include <QStackedLayout>

#include "recGestureWidget.h"

RecGestureWidget::RecGestureWidget(QWidget *parent) : QWidget(parent)
{
    recordGesBegin = false;
    m_rec = new GeometricRecognizer();
    m_rec->loadTemplates();
    setMouseTracking(true);

    this->prePCount = 0;
    this->curPCount = 0;

    connect(this, SIGNAL(writeEmailSig()), parent, SLOT(writeEmail()));
    connect(this, SIGNAL(nextEmailSig()), parent, SLOT(nextEmail()));
    connect(this, SIGNAL(preEmailSig()), parent, SLOT(preEmail()));
    connect(this, SIGNAL(receiveEmailSig()), parent, SLOT(receiveEmail()));
    connect(this, SIGNAL(deleteEmailSig()), parent, SLOT(deleteEmail()));
    connect(this, SIGNAL(curRecognizedGes(QString )), parent, SLOT(curRecognizedGes(QString )));
}

void RecGestureWidget::paintEvent(QPaintEvent *event)
{
    QPainter pt(this);
     pt.setRenderHint(QPainter::Antialiasing, true);
     QPen pen;
     pen.setColor(QColor(255,0,0));
     pen.setWidth(6);
     pt.setPen(pen);

     for (int i=1;i<(int)m_path.size();i++)
    {
        pt.drawLine(QPoint(m_path[i-1].x, m_path[i-1].y), QPoint(m_path[i].x, m_path[i].y));
    }
}

void RecGestureWidget::mouseReleaseEvent(QMouseEvent *event)
{
        mainStaLayout->setStackingMode(QStackedLayout::StackOne);
        mainStaLayout->setCurrentIndex(0);
        mouseGrabber()->releaseMouse();
        recordGesBegin = false;
        if (m_path.size() >= 100)
        {
            //m_recResult = m_rec->recognize(m_path);
            DealWithGesture();
        }
        m_path.clear();
        update();
        //cout<<"RecGestureWidget mouse release"<<endl;
}

void RecGestureWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_path.push_back(Point2D(event->pos().x(), event->pos().y()));

    this->curPCount++;
    if (this->curPCount-this->prePCount >= 100)
    {
        this->prePCount=this->curPCount;
        m_recResult = m_rec->recognize(m_path);
        if (m_recResult.score < 0.7)
        {
             emit curRecognizedGes(QString(tr("None")));
        }
        else
        {
            emit curRecognizedGes(QString::fromStdString(m_recResult.name));
        }
    }


    update();

    //cout<<"RecGestureWidget mouse move"<<endl;
}

void RecGestureWidget::DealWithGesture()
{
    string retName = m_recResult.name;
    double retScore = m_recResult.score;
     if (retScore<0.7)
     {
         return ;
     }

    //QMessageBox::information(this, QString::fromStdString(retName), QString::number(retScore, '.', 0), QMessageBox::Yes);

     if (retName == "V")
     {
         //QMessageBox::information(this, tr(""), tr("Recognize Succeed-V"), QMessageBox::Yes);
         emit writeEmailSig();
         return ;
     }
     else if (retName == "LeftToRightLine")
     {
         //QMessageBox::information(this, tr(""), tr("Recognize Succeed-LeftToRightLine"), QMessageBox::Yes);
          emit nextEmailSig();
          return ;
     }
     else if (retName == "RightToLeftLine")
     {
         //QMessageBox::information(this, tr(""), tr("Recognize Succeed-RightToLeftLine"), QMessageBox::Yes);
         emit preEmailSig();
         return ;
     }
     else if (retName == "Circle")
     {
         //QMessageBox::information(this,tr(""), tr("Recognize Succeed-Circle"), QMessageBox::Yes);
         emit receiveEmailSig();
         return ;
     }
     else if (retName == "X")
     {
         //QMessageBox::information(this, tr(""), tr("Recognize Succeed-X"), QMessageBox::Yes);
         emit deleteEmailSig();
         return ;
     }
}

