#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include "obstacle.h"
#include <QDebug>
#include "widget.h"
#include "sqllitehandler.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent),gameOn(false),score(0), bestScore(0)
{
     setBackgroundMusic();
     user = new QString("");
}

void Scene::startGame()
{

  if(!getGameOn()){

   score = 0;

   setupRoad();
   setupRoadTimer();

   setupClouds();
   setupCloudsTimer();

   setupSkate();

   setupObstaclesTimer();

   showScoreGame();

   setGameOn(true);

   backgroundMusic->play();

  }else{
      cleanScene();
      hideGameOverGraphics();
      hideScoreGame();

      score = 0;

      setupRoad();
      setupRoadTimer();

      setupClouds();
      setupCloudsTimer();

      setupSkate();

      setupObstaclesTimer();

      showScoreGame();

      setGameOn(true);

      backgroundMusic->play();
  }

}

Scene::~Scene()
{
    delete cloudsTimer;
    delete roadTimer;
    delete obstacleTimer;
    delete obstacle;
    delete skateItem;
    delete road;
    delete clouds;
    delete gameOverPix;
    delete scoreTextItem;
    delete backgroundMusic;
    delete user;
}

void Scene::setupCloudsTimer(){

    cloudsTimer = new QTimer();

    connect(cloudsTimer,&QTimer::timeout, [=] () {
       Clouds* cloudsItem = new Clouds();
        cloudsItem->setZValue(0);
        addItem(cloudsItem);
    });

    cloudsTimer->start(9000);
}

void Scene::setupObstaclesTimer(){

    obstacleTimer = new QTimer();

    connect(obstacleTimer,&QTimer::timeout, [=] () {

        obstacle= new Obstacle();
        obstacle->setZValue(2);
         addItem(obstacle);

        connect(obstacle,&Obstacle::collideJump,[=](){
            skateItem->fall();
            emit showButtons();
            gameOver();
           showGameOverGraphics();
            backgroundMusic->stop();

        });

    });

    obstacleTimer->start(5000);
}

void Scene::setupRoadTimer()
{
    roadTimer = new QTimer();

    connect(roadTimer,&QTimer::timeout, [=] () {

       road = new Road();
       road->setZValue(1);
        addItem(road);
    });

    roadTimer->start(6000);
}

void Scene::setupRoad()
{
    road = new Road();
    road->setZValue(1);
    addItem(road);

}

void Scene::setupClouds()
{
    clouds = new Clouds();
    clouds->setZValue(0);
    addItem(clouds);

}

void Scene::setupSkate()
{
    skateItem = new SkateItem(QPixmap(":/Images/s1.png"),QPixmap(":/Images/j1.png"));
    skateItem->setZValue(3);  //prioritate in plan
    addItem(skateItem);
}

void Scene::gameOver()
{

    if( bestScore > maxScorePlayer){
        maxScorePlayer = bestScore;
        SqlLiteHandler::updateScore(*user,maxScorePlayer);
    }

    skateItem->freezeSkate();

   // if(obstacleTimer->isActive()){
    obstacleTimer->stop();
  //  }


   // if(roadTimer->isActive()){
    roadTimer->stop();
   // }


  //  if(cloudsTimer->isActive()){
    cloudsTimer->stop();
   // }

    QList<QGraphicsItem*> sceneItems = items();

    foreach (QGraphicsItem *item, sceneItems) {
        Road *roadItem = dynamic_cast<Road*>(item);
        Obstacle *obstacleItem = dynamic_cast<Obstacle*>(item);
        Clouds *cloudsItem = dynamic_cast<Clouds*>(item);

        if(roadItem){
            roadItem->freezeRoad();
        }else if(obstacleItem){
            obstacleItem->freezeObstacle();
        }else if(cloudsItem){
            cloudsItem->freezeClouds();
        }
    }

}

void Scene::cleanScene()
{
    removeItem(skateItem);
    delete skateItem;

    delete obstacleTimer;
    delete cloudsTimer;
    delete roadTimer;

    QList<QGraphicsItem*> sceneItems = items();

    foreach (QGraphicsItem *item, sceneItems) {
        Road *roadItem = dynamic_cast<Road*>(item);
        Obstacle *obstacleItem = dynamic_cast<Obstacle*>(item);
        Clouds *cloudsItem = dynamic_cast<Clouds*>(item);

        if(roadItem){
           removeItem(roadItem);
           delete item;
        }else if(obstacleItem){
            removeItem(obstacleItem);
            delete item;
        }else if(cloudsItem){
           removeItem(cloudsItem);
           delete item;
        }
    }
}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/Images/gameover.png"));
    gameOverPix->setZValue(4);
   addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) + QPointF(476,50));
}


void Scene::hideGameOverGraphics()
{
    if(gameOverPix){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
       scoreTextItem = nullptr;
    }
}

void Scene::showScoreGame()
{
    scoreTextItem = new QGraphicsTextItem();

    QString htmlString = "<p> Score : " + QString::number(score) + " </p>"
                         + "<p> Best Score : " + QString::number(bestScore) + "</p>";

    QFont mFont("Consolas", 30, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);
    scoreTextItem->setZValue(4);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) + QPointF(1200, 50));
}

void Scene::hideScoreGame()
{
    removeItem(scoreTextItem);
}

void Scene::updateUser(QString *cuser)
{
    *user = *cuser;
    maxScorePlayer = SqlLiteHandler::getScore(*user);
}

void Scene::setScoreGame()
{
    QString htmlString = "<p> Score : " + QString::number(score) + " </p>"
                         + "<p> Best Score : " + QString::number(bestScore) + "</p>";

    scoreTextItem->setHtml(htmlString);
}

void Scene::setBackgroundMusic()
{
   backgroundMusic = new QMediaPlayer();
   backgroundMusic->setMedia(QUrl("qrc:/Sounds/background.mp3"));
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;
    if(score > bestScore){
        bestScore = score;
    }
    setScoreGame();
   // qDebug() << "Score: " <<score << " Best score " << bestScore;
    if(score % 15 == 0){
        backgroundMusic->stop();
        backgroundMusic->play();
    }

}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() ==  Qt::Key_Space){

        if(skateItem->getStateJumping() == false){

       skateItem->setStateJumpingTrue();
       skateItem->skatingTimer->stop();
       skateItem->jumping();

      }
}

    QGraphicsScene::keyPressEvent(event);
}

