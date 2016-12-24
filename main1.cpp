#include "redis.cpp"
#include <stdio.h>
#include "json.h"
#include <QByteArray>
#include <string.h>
#include <QDebug>

int main1()
{
    Redis *r = Redis::getRedis();

    if (!r->connect("127.0.0.1", 6379))
    {
        printf("redis connect err\n");
        return -1;
    }

    Json json;
    json.insert("name", "mco");
    json.insert("age", 18);
    json.insert("sex", "man");
    json.insert("score", 222.22);

    QByteArray buf = json.toJson();

    r->set("name", buf);

    QByteArray test = r->get(QString("name"));

    qDebug() << test << endl;

    delete r;

    return 0;
}
