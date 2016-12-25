#ifndef HCDEF_H
#define HCDEF_H
#include <mysql/mysql.h>
#include <mysql/mysql_com.h>

typedef MYSQL_ROW ROW;
#define HC_PORT 9999
#define HC_CMD "cmd"
#define HC_REG "reg"
#define HC_LOGIN "login"
#define HC_TYPE "type"
#define HC_DRIVER "driver"
#define HC_PASSENGER "passenger"
#define HC_ADDRESS "127.0.0.1"
#define HC_USER "root"
#define HC_PASSWD "123456"
#define HC_DB "HC"
#define HC_REDIS_PORT 6379

typedef enum BOOL{FALSE=0,TRUE=1} Bool;
/*typedef struct _hc{
    int id;
    char buf[0];
}hc;

typedef struct _Passenger{
    char username[64];
    char password[32];
    int age;
    int sex;
    char tel[11];
    char cardId[18];
}Passenger;
*/
#endif // HCDEF_H
