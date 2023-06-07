//
// Created by mkg on 07.06.2023.
//

#include "deviceconnector.h"

DeviceConnector::DeviceConnector() {
    _settings = {};
    readSettingsFromIni();
   // writeLowForPins();
}

DeviceConnector::~DeviceConnector() {
    _settings.clear();
}

void DeviceConnector::readSettingsFromIni() {
    QSettings settings(_configPath, QSettings::IniFormat);
    _settings["pinForOut"] = settings.value("Global/pinForOut").toInt();
    _settings["pinForIn"] = settings.value("Global/pinForIn").toInt();
    _settings["port"] = settings.value("Global/port").toInt();
    _settings["delayMs"] = settings.value("Global/delayMs").toInt();

    if(_settings["pinForOut"] == 0 || _settings["pinForIn"] == 0 || _settings["port"] == 0 || _settings["delayMs"] == 0) {
        qFatal("Settings not loaded!");
    }

    qInfo("Settings read!");
}

void DeviceConnector::sendCommand(const QString command) {
    if(command == "in") {
        digitalWrite(_settings["pinForIn"], LOW);
        delay(_settings["delayMs"]);
        digitalWrite(_settings["pinForIn"], HIGH);
        qInfo("[+] %d sent.\n", _settings["pinForIn"]);
    }else if (command == "out") {
        digitalWrite(_settings["pinForOut"], LOW);
        delay(_settings["delayMs"]);
        digitalWrite(_settings["pinForOut"], HIGH);
        qInfo("[+] %d sent.\n", _settings["pinForOut"]);
    }else {
        qInfo("Unknown command came !");
    }
}

void DeviceConnector::writeLowForPins() {
    wiringPiSetup();
    pinMode(_settings["pinForIn"], INPUT);
    pinMode(_settings["pinForOut"], INPUT);
}
