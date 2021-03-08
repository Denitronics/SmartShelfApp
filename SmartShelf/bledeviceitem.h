#pragma once

#include <QObject>
#include <QtDebug>
#include <qbluetoothlocaldevice.h>
#include <QObject>
#include <QVariant>
#include <QList>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QQmlEngine>
#include <QBluetoothServiceInfo>

class BLEDeviceItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString bleDeviceName READ getBLEDeviceName WRITE setBLEDeviceName NOTIFY bleDeviceNameChanged)
    Q_PROPERTY(QString bleDeviceAddress READ getBLEDeviceAddress WRITE setBLEDeviceAddress NOTIFY bleDeviceAddressChanged)


public:
    explicit BLEDeviceItem(QObject* parent = nullptr);

    static void DeclareQML();

    QString getBLEDeviceName();
    QString getBLEDeviceAddress();

    void setBLEDeviceName(QString strDeviceName);
    void setBLEDeviceAddress(QString strDeviceAddress);

private:

    QString m_strBLEDeviceName = "";
    QString m_strBLEDeviceAddress = "";

signals:
    void bleDeviceNameChanged();
    void bleDeviceAddressChanged();


};

