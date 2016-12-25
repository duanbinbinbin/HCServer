#include "util.h"
#include <stdlib.h>
#include <time.h>
#include <QDateTime>
Util::Util(QObject *parent) : QObject(parent)
{

}
qint64 Util::geohash(double Lat,double Lng,int bits)
{
   //qint64
    return 0;
}
Util *Util::getInstance()
{
    static Util* util = NULL;
    if(util==NULL)
    {
        util = new Util;
    }
    return util;
}

QString Util::getCurrentTime()
{
   qint64 time = QDateTime::currentMSecsSinceEpoch();
   return QString::number(time);
}
QString Util::generId()
{
   srand((unsigned int )time(NULL));
   int i ;
   QString str;
   str = getCurrentTime();
   int res;
   for(i=0;i<15;++i)
   {
       res = rand()%10;
       str+=QString::number(res);
   }
   return str;
}
