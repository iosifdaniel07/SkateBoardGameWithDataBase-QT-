#include "obstacle.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QList>
#include <skateitem.h>
#include "scene.h"

Obstacle::Obstacle():pastObst1(false),pastObst2(false)
{

     int distance = QRandomGenerator::global()->bounded(900,1500);

     QPointF o1 = QPointF(xO1,yO1);
     QPointF o2 = QPointF(distance,yO2);

     int randomNr = QRandomGenerator::global()->bounded(61);//91

     if(randomNr >= 0 && randomNr <= 30){

         obstacle1 = new QGraphicsPixmapItem(QPixmap(":/Images/obs1.png"));
         obstacle2 = new QGraphicsPixmapItem(QPixmap(":/Images/obs2.png"));


     }else if(randomNr > 30 && randomNr <= 60){

         obstacle1 = new QGraphicsPixmapItem(QPixmap(":/Images/obs2.png"));//1
         obstacle2 = new QGraphicsPixmapItem(QPixmap(":/Images/obs1.png"));//3


     }


     obstacle1->setPos(QPointF(-1500,0) + o1);
     obstacle2->setPos(QPointF(-1500,0) + o2);

     xAnimation = new QPropertyAnimation(this,"x",this);

     xAnimation->setStartValue(0);
     xAnimation->setEndValue(6000);//6000
     xAnimation->setEasingCurve(QEasingCurve::Linear);
     xAnimation->setDuration(10000); //10000

     xAnimation->start();

     connect(xAnimation,&QPropertyAnimation::finished, [=](){
         scene()->removeItem(this);
         delete this;
      //  qDebug() << "sters";
     });

      addToGroup(obstacle1);
      addToGroup(obstacle2);
}

Obstacle::~Obstacle()
{
    delete obstacle1;
    delete obstacle2;
    delete xAnimation;
}

qreal Obstacle::x() const
{
    return m_x;
}

void Obstacle::setX(qreal x)
{
    m_x = x;

    if(obstacle1->x() + x  > 1200  && !pastObst1){
        pastObst1 = true;
        QGraphicsScene *mScene = scene();
        Scene *myScene = dynamic_cast<Scene*>(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }


    if(obstacle2->x() + x  > 1200  && !pastObst2){
        pastObst2 = true;
        QGraphicsScene *mScene = scene();
        Scene *myScene = dynamic_cast<Scene*>(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }


   if(collidesWithSkate()){
       emit collideJump();
   }
   setPos(QPointF(0,0) + QPointF(x,yO1));
}

void Obstacle::freezeObstacle()
{
    if(xAnimation->Running){
    xAnimation->stop();
    }
}

bool Obstacle::collidesWithSkate()
{
    QList<QGraphicsItem*> collidingItems = obstacle1->collidingItems();
    collidingItems.append(obstacle2->collidingItems());

    foreach (QGraphicsItem *item, collidingItems) {
        SkateItem *skateItem = dynamic_cast<SkateItem*>(item);
        if(skateItem){
            return  true;
        }
    }
    return false;
}
