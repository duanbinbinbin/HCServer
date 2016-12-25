#include "HCServer.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "def.h"
#include "json.h"
#include "handlerequest.cpp"

HCServer::HCServer(QObject *parent) : QObject(parent)
{
    server = new Tufao::HttpServer;

    if (server->listen(QHostAddress::Any, 12306))
    {
        qDebug() << "listen to 12306 success!" << endl;
    }
    else
    {
        qDebug() << "listen to 12306 error!" << endl;
    }

    connect(server, SIGNAL(requestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&)),
            this, SLOT(slotRequestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&)));
}

/*
* function:
*   Handle user registration and driver.
* param:
*   json: Request data.
*   result: Users and driver registration results are obtained.
* return:
*   int: success return 0, error return is not 0.
*/
int handle_reg(Json& json, QByteArray &result)
{
    int ret = 0;
    Json res_json;

    ret = res_json.insert(HC_CMD, HC_REG);
    // user or driver register interface ...
    ret = reg_userOrDriver(json);
    if (ret != 0)
    {
        res_json.insert(QString(HC_RESULT), QString(HC_ERR));
        res_json.insert(QString(HC_REASON), QString("reg_userOrDriver err"));
        qDebug() << "handle_reg register err: %d" << ret << endl;
    }
    else
    {
       res_json.insert(QString(HC_RESULT),QString(HC_OK));
    }
    result = res_json.toJson();
    return ret;
}

/*
* function:
*   Handle user login and driver.
* param:
*   json: Request data.
*   result: The result of get login.
* return:
*   int: success return 0, error return is not 0.
*/
int handle_login(Json& json, QByteArray &result)
{
    int ret = 0;
    Json res_json;

    res_json.insert(HC_CMD, HC_LOGIN);
    // driver or user login interface ...
    ret = login_userOrDriver(json);
    if (ret != 0)
    {
        res_json.insert(HC_RESULT, HC_ERR);
        res_json.insert(HC_REASON, QString("login_userOrDriver err"));
        qDebug() << "login_userOrDriver user or driver login err: " << ret << endl;
    }
    else
    {
        res_json.insert(HC_RESULT, HC_OK);
    }
    result = res_json.toJson();
    return ret;
}

/*
* function:
*   Update the driver's seat.
* param:
*   json: Request data.
*   result: Get the driver's seat result.
* return:
*   int: success return 0, error return is not 0.
*/
int handle_driverUpdatepos(Json& json, QByteArray &result)
{
    int ret = 0;
    Json res_json;

    res_json.insert(HC_CMD, HC_UPDATEDRIVERPOS);

    // update driver position interface ...
    ret = update_driver_pos(json, res_json);
    if (ret != 0)
    {
        res_json.insert(HC_RESULT, HC_ERR);
        res_json.insert(HC_REASON, QString("update_driver_pos err"));
        qDebug() << "update_driver_pos update driver position err: %d" << ret << endl;
    }
    else
    {
        res_json.insert(HC_RESULT, HC_OK);
    }

    result = res_json.toJson();

    return ret;
}

/*
* function:
*   Update driver status.
* param:
*   json: Request data.
*   result: The driver state results.
* return:
*   int: success return 0, error return is not 0.
*/
int handle_driver_status(Json& json, QByteArray &result)
{
    int ret = 0;
    Json res_json;

    res_json.insert(HC_CMD, HC_UPDATEDRIVERSTATUS);

    // update driver status interface ...
    ret = update_driver_status(json, res_json);
    if (ret != 0)
    {
        res_json.insert(HC_RESULT, HC_ERR);
        res_json.insert(HC_REASON, QString("update_driver_status err"));
        qDebug() << "update_driver_status update driver status err: %d" << ret << endl;
    }
    else
    {
        res_json.insert(HC_RESULT, HC_OK);
    }

    result = res_json.toJson();

    return ret;
}

/*
* function:
*   Handle user with a new state.
* param:
*   json: Request data.
*   result: Get the current state of the user.
* return:
*   int: success return 0, error return is not 0.
*/
int handle_user_status(Json& json, QByteArray &result)
{
    int ret = 0;
    Json res_json;

    res_json.insert(HC_CMD, HC_UPDATEUSERORDERSTATUS);

    // update user status interface ...
    ret = update_user_status(json, res_json);
    if (ret != 0)
    {
        res_json.insert(HC_RESULT, HC_ERR);
        res_json.insert(HC_REASON, QString("update_user_status err"));
        qDebug() << "update_user_status update user status err: %d" << ret << endl;
    }
    else
    {
        res_json.insert(HC_RESULT, HC_OK);
    }

    result = res_json.toJson();

    return ret;
}

/*
* function:
*   Handle user request order.
* param:
*   json: Request data.
*   result: Get the result of the user request order.
* return:
*   int: success return 0, error return is not 0.
*/
int handle_user_request_order(Json& json, QByteArray &result)
{
    int ret = 0;
    Json res_json;

    res_json.insert(HC_CMD, HC_ORDERREQUEST);

    // update user request order interface ...
    ret = user_request_order(json, res_json);
    if (ret != 0)
    {
        res_json.insert(HC_RESULT, HC_ERR);
        res_json.insert(HC_REASON, QString("user_request_order err"));
        qDebug() << "user_request_order user request order err: %d" << ret << endl;
    }
    else
    {
        res_json.insert(HC_RESULT, HC_OK);
    }

    result = res_json.toJson();

    return ret;
}

/*
* function:
*   Update the position of the user.
* param:
*   json: Request data.
*   result: Get the result of the user position result.
* return:
*   int: success return 0, error return is not 0.
*/
int handle_update_user_position(Json& json, QByteArray &result)
{
    int ret = 0;
    Json res_json;

    res_json.insert(HC_CMD, HC_UPDATEUSERPOS);

    // update user position interface ...
    ret = update_user_position(json, res_json);
    if (ret != 0)
    {
        res_json.insert(HC_RESULT, HC_ERR);
        res_json.insert(HC_REASON, QString("update_user_position err"));
        qDebug() << "update_user_position update user position err: %d" << ret << endl;
    }
    else
    {
        res_json.insert(HC_RESULT, HC_OK);
    }

    result = res_json.toJson();

    return ret;
}

/*
* function:
*   Handle the request data.
* param:
*   json: Request data.
*   result: Get the result of the request.
* return:
*   int: success return 0, error return is not 0.
*/
int requestData(Tufao::HttpServerRequest &request, QByteArray &result)
{
    int ret = 0;

    QByteArray data = request.readBody();

    Json json(data);
    QString cmd = json.parse(HC_CMD).toString();

    if (cmd == HC_REG)                                  // driver or user register
    {
         ret = handle_reg(json, result);
    }
    else if(cmd == HC_LOGIN)                            // driver or user login
    {
        ret = handle_login(json, result);
    }
    else if (cmd == HC_UPDATEDRIVERPOS)                 // diver update position
    {
        ret = handle_driverUpdatepos(json, result);
    }
    else if (cmd == HC_UPDATEDRIVERSTATUS)              // update driver status
    {
        ret = handle_driver_status(json, result);
    }
    else if (cmd == HC_ORDERREQUEST)                    // user request order
    {
        ret = handle_user_request_order(json, result);
    }
    else if (cmd == HC_UPDATEUSERPOS)                   // update user position
    {
        ret = handle_update_user_position(json, result);
    }
    else
    {
        qDebug() << "requestData unknown command" << endl;
    }

    return ret;
}

void HCServer::slotRequestReady(Tufao::HttpServerRequest &request, Tufao::HttpServerResponse &response)
{
    int ret = 0;
    QByteArray result;  // Response data

    // request data
    ret = requestData(request, result);
    if (ret != 0)
    {
        qDebug() << "requestData err" << endl;
        return;
    }

    // response data
    response.writeHead(Tufao::HttpResponseStatus::OK);
    response.end(result);    // send data

    qDebug() << "slotRequestReady handle success!" << endl;
}
