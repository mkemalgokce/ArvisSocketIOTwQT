//
// Created by mkg on 07.06.2023.
//

#ifndef ARVISIOTSERVER_DEVICECONNECTOR_H
#define ARVISIOTSERVER_DEVICECONNECTOR_H

#include <wiringPi.h>
#include <QSettings>
#include <QObject>
#include <QMap>

class DeviceConnector: public QObject{
public:
    DeviceConnector();
    ~DeviceConnector();
    void readSettingsFromIni();
    void writeLowForPins();

public slots:
    void sendCommand(const QString command);

private:
    QMap<QString, int> _settings;
    QString _configPath = "./config.ini";
};


#endif //ARVISIOTSERVER_DEVICECONNECTOR_H
