#ifndef RECGESTUREWIDGET_H
#define RECGESTUREWIDGET_H

#include <QWidget>

#include <iostream>
#include <vector>

#include "OneDollar/GeometricRecognizer.h"

using namespace std;
using namespace DollarRecognizer;

class QStackedLayout;

class RecGestureWidget : public QWidget
{
    Q_OBJECT

public:
        RecGestureWidget(QWidget *parent=0);

        bool recordGesBegin;
        vector<QPoint> gesPoint;
        GeometricRecognizer *m_rec;
        RecognitionResult m_recResult;
        Path2D m_path;

        QStackedLayout *mainStaLayout;
        void mySet(QStackedLayout* mainStaLayout){this->mainStaLayout = mainStaLayout;}
        void DealWithGesture();

signals:
        void writeEmailSig();
        void receiveEmailSig();
        void nextEmailSig();
        void preEmailSig();
        void deleteEmailSig();

        void curRecognizedGes(QString );

protected:
        void paintEvent(QPaintEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        //void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);



        int prePCount;
        int curPCount;
};

#endif
