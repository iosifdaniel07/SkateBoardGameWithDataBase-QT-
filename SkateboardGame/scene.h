#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <clouds.h>
#include <QTimer>
#include "obstacle.h"
#include "road.h"
#include "skateitem.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void startGame();
    ~Scene();

    bool getGameOn() const;
    void setGameOn(bool value);
    void incrementScore();

signals:
    void showButtons();

public slots:

private:
    void setupCloudsTimer();
    QTimer *cloudsTimer;
    void setupObstaclesTimer();
    QTimer *obstacleTimer;
    void setupRoadTimer();
    QTimer *roadTimer;
    SkateItem *skateItem;
    Obstacle *obstacle;
    Road *road ;
    Clouds *clouds;
    void setupRoad() ;
    void setupClouds();
    void setupSkate() ;
    void gameOver();
    bool gameOn;
    int score;
    int bestScore;
    int maxScorePlayer;
    QString *user;
    QMediaPlayer *backgroundMusic;

    QGraphicsPixmapItem *gameOverPix;
    QGraphicsTextItem *scoreTextItem;

    void showGameOverGraphics();
    void showScoreGame();
    void setScoreGame();
    void setBackgroundMusic();
    void cleanScene();

public:
    void hideGameOverGraphics();
    void hideScoreGame();
    void updateUser(QString *cuser);

protected:
   void keyPressEvent(QKeyEvent *event);

};

#endif // SCENE_H
