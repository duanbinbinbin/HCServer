#include <stdio.h>
#include "json.h"
#include "def.h"

// handle user or driver register.
int reg_userOrDriver(Json inJson, Json outJson)
{
    int ret = 0;

    QString username = inJson.parse(HC_USERNAME).toString();
    QString password = inJson.parse(HC_PASSWORD).toString();

    return ret;
}

// handle user or driver login.
int login_userOrDriver(Json inJson, Json outJson)
{
    int ret = 0;

    return ret;
}

// handle update driver position.
int update_driver_pos(Json inJson, Json outJson)
{
    int ret = 0;

    return ret;
}

// handle update driver status.
int update_driver_status(Json inJson, Json outJson)
{
    int ret = 0;

    return ret;
}

// handle update driver status.
int update_user_status(Json inJson, Json outJson)
{
    int ret = 0;


    return ret;
}

// handle user request order.
int user_request_order(Json inJson, Json outJson)
{
    int ret = 0;

    return ret;
}

// handle update user position.
int update_user_position(Json inJson, Json outJson)
{
    int ret = 0;

    return ret;
}
