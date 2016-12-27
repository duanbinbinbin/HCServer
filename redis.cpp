#include "Redis.h"
#include "def.h"
#include <QVector>

Redis::Redis(QObject *parent) : QObject(parent)
{
    context = redisConnect(HC_IP, HC_REDIS_PORT);
    if (context->err)
    {
        redisFree(context);
        context = NULL;
        qDebug() << "Connect to redisServer faile";
        exit(1);
    }
}

int Redis::getList(QByteArray& key, QVector<QString>& resultList)
{
    int ret = 0;
    if (key.isEmpty())
    {
        qDebug() << "get list key is null";
        return -1;
    }
    char cmd[1024] = { 0 };
    sprintf(cmd, "lrange %s 0 -1", key.data());
    reply = (redisReply*)redisCommand(context, cmd);
    if(reply->type != REDIS_REPLY_ARRAY)
    {
        qDebug() << "Failed to execute command";
        freeReplyObject(reply);
        redisFree(context);
        return -1;
    }
    size_t i = 0;
    for (i = 0; i < reply->elements; ++i)
    {
        resultList.push_back(QString(reply->element[i]->str));
    }
    freeReplyObject(reply);
    reply = NULL;
    return ret;
}

int Redis::setList(QByteArray &key, QByteArray &value)
{
    int ret = 0;
    if (key.isEmpty() || value.isEmpty())
    {
        qDebug() << "set list key or value is null";
        return -1;
    }
    char cmd[1024] = { 0 };
    sprintf(cmd, "rpush %s %s", key.data(), value.data());
    reply = (redisReply*)redisCommand(context, cmd);
    if(reply == NULL)
    {
        qDebug() << "reply is null!";
        redisFree(context);
        return -1;
    }
    if(!(reply->type == REDIS_REPLY_INTEGER))
    {
        qDebug() << "Execute command failed!";
        freeReplyObject(reply);
        redisFree(context);
        return -1;
    }
    freeReplyObject(reply);
    reply = NULL;
    return ret;
}

int Redis::del(QByteArray &key)
{
    int ret = 0;
    if (key.isEmpty())
    {
        qDebug() << "key is null";
        return -1;
    }
    char cmd[1024] = { 0 };
    sprintf(cmd, "del %s", key.data());
    reply = (redisReply*)redisCommand(context, cmd);
    if(reply->type != REDIS_REPLY_INTEGER)
    {
        qDebug() << "Failed to execute command";
        freeReplyObject(reply);
        redisFree(context);
        return -1;
    }
    freeReplyObject(reply);
    reply = NULL;
    return ret;
}

int Redis::setHash(QByteArray &name, QByteArray &key, QByteArray &value)
{
    int ret = 0;
    if (name.isEmpty() || key.isEmpty() || value.isEmpty())
    {
        qDebug() << "set list name, key or value is null";
        return -1;
    }
    char cmd[1024] = { 0 };
    sprintf(cmd, "hset %s %s %s", name.data(), key.data(), value.data());
    reply = (redisReply*)redisCommand(context, cmd);
    if(reply == NULL)
    {
        qDebug() << "reply is null!";
        redisFree(context);
        return -1;
    }
    if(!(reply->type == REDIS_REPLY_INTEGER))
    {
        qDebug() << "Execute command failed!";
        freeReplyObject(reply);
        redisFree(context);
        return -1;
    }
    freeReplyObject(reply);
    reply = NULL;
    return ret;
}

int Redis::getHash(QByteArray &name, QByteArray &key, QByteArray& result)
{
    int ret = 0;
    if (name.isEmpty() || key.isEmpty())
    {
        qDebug() << "get hash name or key is null";
        return -1;
    }
    char cmd[1024] = { 0 };
    sprintf(cmd, "hget %s %s", name.data(), key.data());
    reply = (redisReply*)redisCommand(context, cmd);
    if(reply->type != REDIS_REPLY_STRING)
    {
        qDebug() << "Failed to execute command";
        freeReplyObject(reply);
        redisFree(context);
        return -1;
    }
    result = QByteArray(reply->str);
    freeReplyObject(reply);
    reply = NULL;
    return ret;
}

Redis::~Redis()
{
    if (reply != NULL)
    {
        freeReplyObject(reply);
        reply = NULL;
    }
    if (context != NULL)
    {
        redisFree(context);
        context = NULL;
    }
}
