#include "HCServer.h"
#include <QCoreApplication>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    new HCServer;

    return app.exec();
}
