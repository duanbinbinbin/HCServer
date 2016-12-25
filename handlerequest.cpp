#include <stdio.h>
#include "json.h"
#include "def.h"
#include "sqlconn.h"

// Handle user or driver register.
int reg_userOrDriver(Json inJson, Json outJson)
{
    int ret = 0;

    QString username = inJson.parse(HC_USERNAME).toString();
    QString password = inJson.parse(HC_PASSWORD).toString();
    int age = inJson.parse("age").toInt();
    int sex = inJson.parse("sex").toInt();
    QString tel = inJson.parse("tel").toString();
    QString id = inJson.parse("id").toString();
    QString cardid = inJson.parse("cardid").toString();

    QString sql = QString("insert into passenger values('%1','%2','%3','%4','%5','%6','%7')").arg(id).arg(username)
                    .arg(password).arg(age).arg(sex).arg(tel).arg(cardid);
    ret = SqlConn::getInstance()->insert(sql);
    qDebug() << "reg_userOrDriver ret :" << ret << endl;
    if (ret != 0)
    {
        qDebug() << "insert data err: " << ret << endl;
    }

    return ret;
}

// Handle user or driver login.
int login_userOrDriver(Json inJson, Json outJson)
{
    int ret = 0;
    QByteArray *out = new QByteArray;

    QString username = inJson.parse(HC_USERNAME).toString();
    QString password = inJson.parse(HC_PASSWORD).toString();

    QString sql = QString("select * from passenger where username=%1 and password=%2").arg(username).arg(password);

    ret = SqlConn::getInstance()->selData(sql, out);
    if (ret <=0 )
    {
        qDebug() << "login err: %d" << ret << endl;
        return 1;
    }

    return ret;
}

// Handle update driver position.
int update_driver_pos(Json inJson, Json outJson)
{
    int ret = 0;


    return ret;
}

// Handle update driver status.
int update_driver_status(Json inJson, Json outJson)
{
    int ret = 0;

    return ret;
}

// Handle update driver status.
int update_user_status(Json inJson, Json outJson)
{
    int ret = 0;


    return ret;
}

// Handle user request order.
int user_request_order(Json inJson, Json outJson)
{
    int ret = 0;

    return ret;
}

// Handle update user position.
int update_user_position(Json inJson, Json outJson)
{
    int ret = 0;

    return ret;
}
