#ifndef HCSERVER_H
#define HCSERVER_H

#include <QObject>
#include "HCServer.h"
#include <Tufao/HttpServer>
#include <Tufao/HttpServerRequest>
#include <Tufao/HttpServerResponse>

class HCServer : public QObject
{
    Q_OBJECT
public:
    explicit HCServer(QObject *parent = 0);

    Tufao::HttpServer *server;

signals:

public slots:
    void slotRequestReady(Tufao::HttpServerRequest&,Tufao::HttpServerResponse&);
};

#endif // HCSERVER_H
