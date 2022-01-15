#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Road : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal  x READ x WRITE setX)

public:
    explicit Road();
    ~Road();

    qreal x() const;

signals:

public slots:
      void setX(qreal x);
      void freezeRoad();

private:
    QGraphicsPixmapItem *road ;
    QPropertyAnimation *xAnimation;
    qreal m_x;
};

#endif // ROAD_H
