#ifndef UTIL_H
#define UTIL_H

#include <QObject>

class Util : public QObject
{
    Q_OBJECT
public:
    static Util* getInstance();
    QString getCurrentTime();
    qint64 geohash(double Lat,double Lng,int bits);
    QString generId();
private:
     explicit Util(QObject *parent = 0);
signals:

public slots:
};

#endif // UTIL_H
