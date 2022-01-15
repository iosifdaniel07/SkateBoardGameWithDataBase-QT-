#include "road.h"
#include <QDebug>
#include <QGraphicsScene>

Road::Road()
{

         road = new QGraphicsPixmapItem(QPixmap(":/Images/road.png"));
         road->setPos(QPointF(-4000,640));//-4000,640

         xAnimation = new QPropertyAnimation(this,"x",this);

         xAnimation->setStartValue(0);
         xAnimation->setEndValue(6000);//6000
         xAnimation->setEasingCurve(QEasingCurve::Linear);
         xAnimation->setDuration(10000);//10000


          xAnimation->start();

         connect(xAnimation,&QPropertyAnimation::finished, [=](){
             scene()->removeItem(this);
             delete this;
            //qDebug() << "sters 2";
         });

          addToGroup(road);

}

Road::~Road()
{
    delete road;
    delete xAnimation;
}

qreal Road::x() const
{
    return m_x;
}

void Road::setX(qreal x)
{
     m_x = x;
    // qDebug() << x;
     setPos(QPointF(0,0) + QPointF(x,0));
}

void Road::freezeRoad()
{
    if(xAnimation->Running){
    xAnimation->stop();
    }
}

