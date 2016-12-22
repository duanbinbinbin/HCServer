#ifndef JSON_H
#define JSON_H

#include <QObject>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class Json : public QObject
{
    Q_OBJECT
public:
    explicit Json(QObject *parent = 0);
    explicit Json(QByteArray array,QObject *parent = 0);
    QString encry(QString key);
    int insert(QString key,QString value);
    int insert(QString key,int value);
    int insert(QString key,double value);
    QJsonValue parse(QString key);
    QByteArray toJson();
    ~Json();
private:
    QJsonObject *obj;
};

#endif // JSON_H
