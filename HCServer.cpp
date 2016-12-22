#include "HCServer.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "def.h"
#include "json.h"

HCServer::HCServer(QObject *parent) : QObject(parent)
{
    server = new Tufao::HttpServer;

    if (server->listen(QHostAddress::Any, 8080))
    {
        qDebug() << "listen to 8080 success!" << endl;
    }
    else
    {
        qDebug() << "listen to 8080 error!" << endl;
    }

    connect(server, SIGNAL(requestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&)),
            this, SLOT(slotRequestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&)));
}

// handle register
// result: handle result
int handle_reg(Json json, QString &result)
{
    int ret = 0;
    QString username = json.parse(HC_USERNAME);
    QString password = json.parse(HC_PASSWORD);

    // register interface ...   result...
    ret = registerInterface(username, password);
    if (ret != 0)
    {
        result = HC_ERR;
        qDebug() << "handle_reg register err" << endl;
    }
    else
    {
        result = HC_OK;
    }

    return ret;
}

/*
* function: handle user or dirver login
* result: get login result
*/
int handle_login(Json json, QString &result)
{
    int ret = 0;

    QString username = json.parse(HC_USERNAME);
    QString password = json.parse(HC_PASSWORD);

    // login interface ...
    ret = loginInterface(username, password);
    if (ret != 0)
    {
        result = HC_ERR;
        qDebug() << "handle_login login err" << endl;
    }
    else
    {
        result = HC_OK;
    }

    return ret;
}

/*function: request data
  result: handle result
  command: handle cmd
*/
int requestData(Tufao::HttpServerRequest &request, QString &result, QString &command)
{
    int ret = 0;

    QByteArray data = request.readBody();

    Json json(data);
    QString cmd = json.parse(HC_CMD).toString();

    switch (cmd) {
    case HC_REG:    // driver or user register
        ret = handle_reg(json, result);
        break;

    case HC_LOGIN:  // driver or user login
        ret = handle_login(json, result);
        break;

    default:
        qDebug() << "requestData unknown command" << endl;
        break;
    }
    command = cmd;

    return ret;
}

/* function: handle response reg
 * result: handle result
 * */
int response_reg(Tufao::HttpServerResponse &response, QString &result)
{
    Json res_json;
    res_json.insert(HC_CMD, HC_REG);
    res_json.insert(HC_RESULT, result);
    if (result != HC_OK)    // if resgister err
    {
        res_json.insert(HC_REASON, QString("register err"));
    }

    QByteArray res_buf = res_json.toJson();
    response.writeHead(Tufao::HttpResponseStatus::OK);
    response.end(res_buf);
}

int response_login(Tufao::HttpServerResponse &response, QString &result)
{
    Json login_json;
    login_json.insert(HC_CMD, HC_LOGIN);
    login_json.insert(HC_RESULT, result);
    if (result != HC_OK)    // if login err
    {
        login_json.insert(HC_REASON, QString("login err"));
    }

    QByteArray login_buf = login_json.toJson();
    response.writeHead(Tufao::HttpResponseStatus::OK);
    response.end(login_buf);
}

/*function: response data
  result: handle result
  command: handle cmd
*/
int responseData(Tufao::HttpServerResponse &response, QString &result, QString &command)
{
    int ret = 0;

    switch (command) {

    case HC_REG:
        ret = response_reg(response, result);
        break;

    case HC_LOGIN:
        ret = response_login(response, result);
        break;

    default:
        qDebug() << "requestData unknown command" << endl;
        break;
    }

    return ret;
}

void HCServer::slotRequestReady(Tufao::HttpServerRequest &request, Tufao::HttpServerResponse &response)
{
    int ret = 0;
    QString result;
    QString command;

    // request data
    ret = requestData(request, result, command);
    if (ret != 0)
    {
        qDebug() << "requestData err" << endl;
        return;
    }

    // response data
    ret = responseData(response, result, command);
    if (ret != 0)
    {
        qDebug() << "responseData err" << endl;
        return;
    }

    qDebug() << "slotRequestReady handle success" << endl;
}
