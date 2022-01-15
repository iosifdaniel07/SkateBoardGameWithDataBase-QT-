#include "skateitem.h"

SkateItem::SkateItem(QPixmap pixmap1,QPixmap pixmap2):
            pixmap1(pixmap1),pixmap2(pixmap2), isJumping(false)
{

     skating();

    jumpMusic = new QMediaPlayer();
    jumpMusic->setMedia(QUrl("qrc:/Sounds/Skateboard_Jump.mp3"));
   // jumpMusic->setVolume(100);

}

SkateItem::~SkateItem()
{
    delete jumpingTimer;
    delete skatingTimer;
    delete  jumpMusic;
}

void SkateItem::skating()
{
    skatingPosition = SkatingPosition::one;
    setPixmap(pixmap1);
    setPos(900,405);

    skatingTimer = new QTimer(this);
    connect(skatingTimer,&QTimer::timeout,[=](){
        updatePixmap();
    });
    skatingTimer->start(90);
}

void SkateItem::jumping()
{
    jumpPosition = JumpPosition::j4; //j1
    setPixmap(pixmap2);
    setPos(948,465);

    jumpingTimer = new QTimer(this);
    connect(jumpingTimer,&QTimer::timeout,[=](){
          updateJumpPixmap();
     });
    jumpingTimer->start(100);//90
}

void SkateItem::freezeSkate()
{
    if(skatingTimer->isActive()){
         skatingTimer->stop();
    }else{
         jumpingTimer->stop();
    }
}

void SkateItem::setStateJumpingTrue()
{
    isJumping = true;
}

bool SkateItem::getStateJumping()
{
    return isJumping;
}

void SkateItem::fall()
{
     setPixmap(QPixmap(":/Images/fall.png"));
     setPos(QPointF(700,590));
}


void SkateItem::updateJumpPixmap(){

    if(isJumping == true){

       jumpMusic->play();

    if(jumpPosition == JumpPosition::j1){
        jumpPosition = JumpPosition::j2;
        setPixmap(QPixmap(":/Images/j2.png"));
       setPos(922,465);
    }else if(jumpPosition == JumpPosition::j2){
        jumpPosition = JumpPosition::j3;
        setPixmap(QPixmap(":/Images/j3.png"));
        setPos(934,475);//495
    }else if(jumpPosition == JumpPosition::j3){
        jumpPosition = JumpPosition::j4;
        setPixmap(QPixmap(":/Images/j4.png"));
        setPos(934,480);//500
    }else if(jumpPosition == JumpPosition::j4){
        jumpPosition = JumpPosition::j5;
        setPixmap(QPixmap(":/Images/j5.png"));
         setPos(924,470);//490
    }else if(jumpPosition == JumpPosition::j5){
        jumpPosition = JumpPosition::j6;
        setPixmap(QPixmap(":/Images/j6.png"));
        setPos(965,400);//440
    }else if(jumpPosition == JumpPosition::j6){
        jumpPosition = JumpPosition::j7;
        setPixmap(QPixmap(":/Images/j7.png"));
        setPos(916,160);//200
    }else if(jumpPosition == JumpPosition::j7){
        jumpPosition = JumpPosition::j8;
        setPixmap(QPixmap(":/Images/j8.png"));
        setPos(906,150);//200
    }else if(jumpPosition == JumpPosition::j8){
        jumpPosition = JumpPosition::j9;
        setPixmap(QPixmap(":/Images/j9.png"));
         setPos(922,180);//230
    }else if(jumpPosition == JumpPosition::j9){
        jumpPosition = JumpPosition::j10;
        setPixmap(QPixmap(":/Images/j10.png"));
         setPos(915,180);//230
    }else if(jumpPosition == JumpPosition::j10){
        jumpPosition = JumpPosition::j11;
        setPixmap(QPixmap(":/Images/j11.png"));
        setPos(914,180);//230
    }else if(jumpPosition == JumpPosition::j11){
        jumpPosition = JumpPosition::j12;
        setPixmap(QPixmap(":/Images/j12.png"));
        setPos(914,180);//230
    }else if(jumpPosition == JumpPosition::j12){
        jumpPosition = JumpPosition::j13;
        setPixmap(QPixmap(":/Images/j13.png"));
         setPos(914,230);//270
    }else if(jumpPosition == JumpPosition::j13){
        jumpPosition = JumpPosition::j14;
        setPixmap(QPixmap(":/Images/j14.png")); //
         setPos(962,270);//305
    }else if(jumpPosition == JumpPosition::j14){
        jumpPosition = JumpPosition::j15;
        setPixmap(QPixmap(":/Images/j15.png"));
        setPos(900,270);//305
    }else if(jumpPosition == JumpPosition::j15){
        jumpPosition = JumpPosition::j16;
        setPixmap(QPixmap(":/Images/j16.png"));
         setPos(922,440);//440
    }else if(jumpPosition == JumpPosition::j16){
         // jumpPosition = JumpPosition::j1;
        //  setPixmap(QPixmap(":/Images/j1.png"));
        //  setPos(948,465);

        isJumping = false;
        jumpingTimer->stop();

        jumpMusic->stop();

        skating();
    }

 }

}

void SkateItem::updatePixmap(){

    if(skatingPosition == SkatingPosition::one){
           skatingPosition = SkatingPosition::two;
           setPixmap(QPixmap(":/Images/s2.png"));
           setPos(913,382);
       }else if(skatingPosition == SkatingPosition::two){
           skatingPosition = SkatingPosition::three;
           setPixmap(QPixmap(":/Images/s3.png"));
           setPos(900,398);
       }else if(skatingPosition == SkatingPosition::three){
           skatingPosition = SkatingPosition::four;
           setPixmap(QPixmap(":/Images/s4.png"));
            setPos(914,425);
       }else if(skatingPosition == SkatingPosition::four){
           skatingPosition = SkatingPosition::five;
           setPixmap(QPixmap(":/Images/s5.png"));
            setPos(900,422);
       }else if(skatingPosition == SkatingPosition::five){
           skatingPosition = SkatingPosition::six;
           setPixmap(QPixmap(":/Images/s6.png"));
             setPos(890,420);
       }else if(skatingPosition == SkatingPosition::six){
           skatingPosition = SkatingPosition::seven;
           setPixmap(QPixmap(":/Images/s7.png"));
           setPos(902,446);
       }else if(skatingPosition == SkatingPosition::seven){
           skatingPosition = SkatingPosition::eight;
           setPixmap(QPixmap(":/Images/s8.png"));
           setPos(874,444);
       }else if(skatingPosition == SkatingPosition::eight){
           skatingPosition = SkatingPosition::nine;
           setPixmap(QPixmap(":/Images/s9.png"));
           setPos(870,454);
       }else if(skatingPosition == SkatingPosition::nine){
           skatingPosition = SkatingPosition::ten;
           setPixmap(QPixmap(":/Images/s10.png"));
               setPos(885,468);
       }else if(skatingPosition == SkatingPosition::ten){
           skatingPosition = SkatingPosition::eleven;
           setPixmap(QPixmap(":/Images/s11.png"));
          setPos(914,480);
       }else if(skatingPosition == SkatingPosition::eleven){
           skatingPosition = SkatingPosition::twelve;
           setPixmap(QPixmap(":/Images/s12.png"));
             setPos(930,464);
       }else if(skatingPosition == SkatingPosition::twelve){
           skatingPosition = SkatingPosition::thirteen;
           setPixmap(QPixmap(":/Images/s13.png"));
           setPos(935,450);
       }else if(skatingPosition == SkatingPosition::thirteen){
           skatingPosition = SkatingPosition::fourteen;
           setPixmap(QPixmap(":/Images/s14.png"));
           setPos(928,425);
       }else if(skatingPosition == SkatingPosition::fourteen){
           skatingPosition = SkatingPosition::fithteen;
           setPixmap(QPixmap(":/Images/s15.png"));
            setPos(926,418);
       }else if(skatingPosition == SkatingPosition::fithteen){
           skatingPosition = SkatingPosition::sixteen;
           setPixmap(QPixmap(":/Images/s16.png"));
          setPos(904,408);
       }else if(skatingPosition == SkatingPosition::sixteen){
           skatingPosition = SkatingPosition::seventeen;
           setPixmap(QPixmap(":/Images/s17.png"));
           setPos(918,420);
       }else if(skatingPosition == SkatingPosition::seventeen){
           skatingPosition = SkatingPosition::eightteen;
           setPixmap(QPixmap(":/Images/s18.png"));
           setPos(925,418);
       }else if(skatingPosition == SkatingPosition::eightteen){
           skatingPosition = SkatingPosition::nineteen;
           setPixmap(QPixmap(":/Images/s19.png"));
            setPos(930,417);
       }else if(skatingPosition == SkatingPosition::nineteen){
           skatingPosition = SkatingPosition::twenty;
           setPixmap(QPixmap(":/Images/s20.png"));
           setPos(900,422);
       }else if(skatingPosition == SkatingPosition::twenty){
           skatingPosition = SkatingPosition::one;
           setPixmap(QPixmap(":/Images/s1.png"));
            setPos(900,405);
       }
}
