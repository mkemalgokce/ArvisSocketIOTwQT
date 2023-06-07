#include <QCoreApplication>
#include "websocketserver.h"
#include "deviceconnector.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    a.setApplicationName("Arvis IOT Server");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("ArVis Teknoloji");


    auto* connector = new DeviceConnector;
    auto* server = new WebSocketServer;

    QObject::connect(server, &WebSocketServer::commandCame, connector, &DeviceConnector::sendCommand);
    return a.exec();

}
