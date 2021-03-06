#ifndef WORLD_H
#define WORLD_H

#include <QVector>
#include "Box2D.h"
#include "car.h"
#include "contactlistener.h"
#include "geneticalgorithm.h"
#include "track.h"

class ContactListener;

class World: public QObject {
    Q_OBJECT
public:
    World();
    ~World();

    void addSparksList(const int impulses, const b2Vec2 pos,
                       const QColor *color);
    GeneticAlgorithm *getAlgorithm();
    Car *getCar();
    b2Vec2 getCenter();
    Track *getTrack();
    b2Body *getSpark(const int index);
    int getSparkCount();
    float getUptime();
    void step();

signals:
    void creteNewCar();
    void freeCallListNumber(unsigned int);

public slots:
    void carStoped();

private:
    struct sparkStuct {
        int count;
        b2Vec2 pos;
        const QColor *color;
    };

    static const float GRAVITY = -15.0;
    static const int ITERATIONS = 30;
    static const float TIME_STEP = 1.0/60.0;
    static const int MAX_SPARK_COUNT = 512;

    void destroy();
    void destroySpark(const int index);
    void init();
    void updateSparks();

    GeneticAlgorithm *algorithm;
    b2World *b2world;
    Car *car;
    ContactListener *contactListener;
    QVector<b2Fixture *> sparks;
    QVector<sparkStuct> sparkList;
    Track *track;
    float uptime;
};

#endif // WORLD_H
