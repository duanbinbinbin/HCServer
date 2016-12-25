#ifndef SQLCONN_H
#define SQLCONN_H

#include <QObject>
#include <mysql/mysql.h>
#include <QByteArray>
class SqlConn : public QObject
{
    Q_OBJECT
public:
    static SqlConn* getInstance();
    int insert(QString str);
    ~SqlConn();
    int selData(QString str,QByteArray* array);
    int update(QString str);
private:
    explicit SqlConn(QObject *parent = 0);
    MYSQL* sql;

signals:

public slots:
};

#endif // SQLCONN_H
