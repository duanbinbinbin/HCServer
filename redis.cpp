/* ************************************************************************
 *       Filename:  redis.c
 *    Description:  
 *        Version:  1.0
 *        Created:  12/23/2016 06:26:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#ifndef _REDIS_H_
#define _REDIS_H_
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <hiredis/hiredis.h>
#include <QByteArray>
#include <QString>

class Redis {
	public:
        static Redis* getRedis()
        {
            static Redis* _redis = NULL;
            if (_redis == NULL)
            {
                _redis = new Redis;
            }
            return _redis;
        }

		~Redis() {
			this->_connect = NULL;
			this->_reply = NULL;
		} 

		bool connect(std::string host, int port) {
			this->_connect = redisConnect(host.c_str(), port);
			if(this->_connect != NULL && this->_connect->err) {
				printf("connect error: %s\n", this->_connect->errstr);
				return 0;
            }
            return 1;
		} 

        QByteArray get(QString key)
        {
            std::string buf = get(key.toStdString());
            return QByteArray::fromStdString(buf);
        }

        void set(QString key, QByteArray value)
        {
            set(key.toStdString(), value.toStdString());
        }

	private:

        Redis(){}

        Redis(const Redis&){}

        Redis& operator=(const Redis&){}

		redisContext* _connect;
        redisReply* _reply;

        void set(std::string key, std::string value) {
            redisCommand(this->_connect, "SET %s %s", key.c_str(), value.c_str());
        }

        std::string get(std::string key) {
            this->_reply = (redisReply*)redisCommand(this->_connect,
                    "GET %s", key.c_str());
            std::string str = this->_reply->str;
            freeReplyObject(this->_reply);
            return str;
        }
};
#endif



