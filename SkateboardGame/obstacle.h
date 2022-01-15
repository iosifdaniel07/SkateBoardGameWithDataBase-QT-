#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Obstacle : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal  x READ x WRITE setX)
public:
    explicit Obstacle();
    ~Obstacle();

    qreal x() const;

signals:
     void collideJump();

public slots:
    void setX(qreal x);
    void freezeObstacle();
private:
    QGraphicsPixmapItem *obstacle1 ;
    QGraphicsPixmapItem *obstacle2 ;
    QPropertyAnimation *xAnimation ;
    int xO1 = 0, yO1 = 650;
    int xO2 = 0, yO2 = 650;
    qreal m_x;
    bool collidesWithSkate();
    bool pastObst1;
    bool pastObst2;
};

#endif // OBSTACLE_H
