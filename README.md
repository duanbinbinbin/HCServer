# HCServer
Tufao服务器

### redis接口使用：

  > 连接到redis:  `bool connect(string ip, int port);`
 
  > 添加到redis： `void set(QString key, QByteArray value);`
 
  > 得到redis:    `QByteArray get(QString key);`
