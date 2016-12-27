#ifndef REDIS_H
#define REDIS_H

#include <QObject>
#include <hiredis/hiredis.h>
#include <QDebug>
#include <QByteArray>
#include <QVector>

class Redis : public QObject
{
    Q_OBJECT
public:
    explicit Redis(QObject *parent = 0);

    int getList(QByteArray &key, QVector<QString> &resultList);
    int setList(QByteArray &key, QByteArray &value);

    int del(QByteArray &key);

    int setHash(QByteArray& name, QByteArray& key, QByteArray& value);
    int getHash(QByteArray& name, QByteArray& key, QByteArray& result);

    ~Redis();

private:
    redisContext* context;
    redisReply* reply;

signals:

public slots:
};

#endif // REDIS_H
