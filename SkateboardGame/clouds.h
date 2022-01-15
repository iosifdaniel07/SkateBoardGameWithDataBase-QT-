#ifndef CLOUDS_H
#define CLOUDS_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Clouds : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    explicit Clouds();
    ~Clouds();
qreal x() const;

signals:

public slots:
void setX(qreal x);
void freezeClouds();

private:
QGraphicsPixmapItem *cloud1 , *cloud2 , *cloud3 ;
QPropertyAnimation *xAnimation;
qreal m_x;
int xC1 = 100, yC1 = 100; //180
int xC2 = 700, yC2 = 80;//100
int xC3 = 1200, yC3 = 120;//240

};

#endif // CLOUDS_H
