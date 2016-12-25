#include "json.h"
#include <QDebug>
Json::Json(QObject *parent) : QObject(parent)
{
    //obj = new QJsonObject;
}

Json::Json(QByteArray array, QObject *parent): QObject(parent)
{
    //obj = new QJsonObject;
    obj = QJsonDocument::fromJson(array).object();
}

Json::Json(const Json &json)
{
    obj = json.obj;
}

QString Json::encry(QString key)
{
    char* tmp = key.toUtf8().data();
    return QString(QCryptographicHash::hash(QByteArray(tmp),QCryptographicHash::Md5).toHex());
}

int Json::insert(QString key, QString value)
{
    if(key.isEmpty() || value.isEmpty())
    {
        qDebug() << "key or value is empty!";
        return -1;
    }
    obj.insert(key,value);
    return 0;
}

int Json::insert(QString key, int value)
{
    if(key.isEmpty())
    {
        qDebug() << "key  is empty!";
        return -1;
    }
    obj.insert(key,value);
    return 0;
}

int Json::insert(QString key, double value)
{
    if(key.isEmpty() )
    {
        qDebug() << "key  is empty!";
        return -1;
    }
    obj.insert(key,value);
    return 0;
}

QJsonValue Json::parse(QString key)
{
    return obj.value(key);
}

QByteArray Json::toJson()
{
    QJsonDocument doc(obj);
    return doc.toJson();
}

Json::~Json()
{
//    if(obj!=NULL){
//        delete obj;
//        obj = NULL;
//    }
}
