#include <stdio.h>
#include "json.h"
#include "def.h"
#include "sqlconn.h"
#include <QDebug>
#include "Redis.h"
#include <QByteArray>
#include <QVector>

// Handle user or driver register.
int reg_userOrDriver(QByteArray& inData)
{
    int ret = 0;
    Json inJson(inData);
    QString sql;
    QString identity = inJson.parse(HC_IDENTITY).toString();
    QString username = inJson.parse(HC_USERNAME).toString();
    QString password = inJson.parse(HC_PASSWORD).toString();
    int age = inJson.parse("age").toInt();
    int sex = inJson.parse("sex").toInt();
    QString tel = inJson.parse("tel").toString();
    QString id = inJson.parse("id").toString();
    QString cardid = inJson.parse("cardid").toString();

    if (identity == HC_PASSENGER)
    {
        sql = QString("insert into passenger values('%1','%2','%3','%4','%5','%6','%7')").arg(id).arg(username)
                        .arg(password).arg(age).arg(sex).arg(tel).arg(cardid);
    }
    else
    {
        QString carid = inJson.parse("carid").toString();
        sql = QString("insert into driver values('%1','%2','%3','%4','%5','%6','%7','%8')").arg(id).arg(username)
                .arg(password).arg(age).arg(sex).arg(tel).arg(cardid).arg(carid);
    }
    ret = SqlConn::getInstance()->insert(sql);
    if (ret != 0)
    {
        qDebug() << "insert data err: " << ret << endl;
    }
    return ret;
}

// Handle user or driver login.
int login_userOrDriver(QByteArray& inData)
{
    int ret = 0;
    Json inJson(inData);
    QByteArray *out = new QByteArray;
    QString sql;
    QString identity = inJson.parse(HC_IDENTITY).toString();
    QString username = inJson.parse(HC_USERNAME).toString();
    QString password = inJson.parse(HC_PASSWORD).toString();

    if (identity == HC_PASSENGER)
    {
        sql = QString("select * from passenger where username='%1' and password='%2'").arg(username).arg(password);
    }
    else
    {
        sql = QString("select * from driver where username='%1' and password='%2'").arg(username).arg(password);
    }
    ret = SqlConn::getInstance()->selData(sql, out);
    if (out->isEmpty())
    {
        qDebug() << "login err : " << ret << endl;
        return 1;
    }
    delete out;
    return 0;
}

// Handle update driver position.
int update_driver_pos(Json inJson)
{
    int ret = 0;
    QString username = inJson.parse(HC_USERNAME).toString();
    double lat = inJson.parse(HC_LAT).toDouble();
    double lng = inJson.parse(HC_LNG).toDouble();
    QString geohash = inJson.parse(HC_GEOHASH).toString();

    return ret;
}

// Handle update driver status.
int update_driver_status(Json inJson)
{
    int ret = 0;
    QString username = inJson.parse(HC_USERNAME).toString();
    QString status = inJson.parse(HC_STATUS).toString();

    return ret;
}

/*
司机已经接单 1
乘客已经上车状态 2
fini 3
取消状态 4
*/
// Handle update driver status.
int update_user_status(Json inJson, Json outJson)
{
    int ret = 0;
    QString username = inJson.parse(HC_USERNAME).toString();
    QString orderid = inJson.parse(HC_ORDERID).toString();
    int status = inJson.parse(HC_STATUS).toInt();

    return ret;
}

/* success response.
{
  cmd: "orderrequest",
  result: "ok",

  username: "driver username",
  carid: "carid",
  tel: "driver tel",
  orderid: 111111,
  lat: 13.111,
  lng: 15.111
}
*/
// Handle user request order.
int user_request_order(Json inJson, Json outJson)
{
    int ret = 0;
    QString username = inJson.parse(HC_USERNAME).toString();
    double lat_begin = inJson.parse(HC_LATBEGIN).toDouble();    // user begin lat
    double lng_begin = inJson.parse(HC_LNGBEGIN).toDouble();    // user begin lng
    double lat_end = inJson.parse(HC_LATEND).toDouble();
    double lng_end = inJson.parse(HC_LNGEND).toDouble();
    QString geohash = inJson.parse(HC_GEOHASH).toString();
    QString tel = inJson.parse(HC_TEL).toString();

    return ret;
}

/* success response.
{
  cmd: "updatepos",
  lat: "driver's pos",
  lng: "driver's pos"
}
*/
// Handle update user position.
int update_user_position(Json inJson, Json outJson)
{
    int ret = 0;
    QString username = inJson.parse(HC_USERNAME).toString();
    double lat = inJson.parse(HC_LAT).toDouble();
    double lng = inJson.parse(HC_LNG).toDouble();

    return ret;
}
