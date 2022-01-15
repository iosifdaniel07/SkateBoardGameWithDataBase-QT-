#include "clouds.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsScene>

Clouds::Clouds() : cloud1(new QGraphicsPixmapItem(QPixmap(":/Images/nor1.png"))), cloud2(new QGraphicsPixmapItem(QPixmap(":/Images/nor2.png"))),
    cloud3(new QGraphicsPixmapItem(QPixmap(":/Images/nor3.png")))
{

     int randomNr = QRandomGenerator::global()->bounded(91);

     QPointF c1 = QPointF(xC1,yC1);
     QPointF c2 = QPointF(xC2,yC2);
     QPointF c3 = QPointF(xC3,yC3);



     if(randomNr >= 0 && randomNr <= 30){

         cloud1->setPos(QPointF(-1500,0) + c1);
         cloud2->setPos(QPointF(-1500,0) + c2);
         cloud3->setPos(QPointF(-1500,0) + c3);

     }else if(randomNr > 30 && randomNr <= 60){

         cloud1->setPos(QPointF(-1500,0) + c2);
         cloud2->setPos(QPointF(-1500,0) + c3);
         cloud3->setPos(QPointF(-1500,0) + c1);

     }else if(randomNr >= 60 && randomNr <= 91){

         cloud1->setPos(QPointF(-1500,0) + c3);
         cloud2->setPos(QPointF(-1500,0) + c1);
         cloud3->setPos(QPointF(-1500,0) + c2);
     }

     //qDebug() << randomNr;

     xAnimation = new QPropertyAnimation(this,"x",this);


     xAnimation->setStartValue(0);
     xAnimation->setEndValue(3000);
     xAnimation->setEasingCurve(QEasingCurve::Linear);
     xAnimation->setDuration(16000);

     xAnimation->start();

     connect(xAnimation,&QPropertyAnimation::finished, [=](){
         scene()->removeItem(this);
         delete this;
       //  qDebug() << "sters";
     });


     addToGroup(cloud1);
     addToGroup(cloud2);
     addToGroup(cloud3);

}

Clouds::~Clouds()
{
    delete cloud1;
    delete cloud2;
    delete cloud3;
    delete xAnimation;
}

qreal Clouds::x() const
{
    return m_x;
}

void Clouds::setX(qreal x)
{
    m_x = x;
   // qDebug() << x;
    setPos(QPointF(0,0) + QPointF(x,yC1));
}

void Clouds::freezeClouds()
{
    if(xAnimation->Running){
         xAnimation->stop();
    }
}
