#ifndef SKATEITEM_H
#define SKATEITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMediaPlayer>

class SkateItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SkateItem(QPixmap pixmap1,QPixmap pixmap2);
    ~SkateItem();

signals:

public slots:

private:
   enum SkatingPosition{
       one,two,three,four,five,
       six,seven,eight,nine,ten,eleven,twelve,
       thirteen,fourteen,fithteen,sixteen,seventeen,
       eightteen,nineteen,twenty
    };

   enum JumpPosition{
       j1,j2,j3,j4,j5,j6,j7,j8,j9,j10,j11,j12,j13,j14,j15,j16
   };

   SkatingPosition skatingPosition;
   JumpPosition jumpPosition;
   QPixmap pixmap1;
   QPixmap pixmap2;
   void updatePixmap();
   void updateJumpPixmap();
    bool isJumping;
    QMediaPlayer *jumpMusic;


public:
   void skating();
   void jumping();
   QTimer *skatingTimer ;
   QTimer *jumpingTimer ;
   void freezeSkate();
   void setStateJumpingTrue();
   bool getStateJumping();
   void fall();
};

#endif // SKATEITEM_H
