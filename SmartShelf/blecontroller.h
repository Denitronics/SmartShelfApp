#ifndef BLECONTROLLER_H
#define BLECONTROLLER_H

#include <QObject>
#include <QtDebug>
#include <qbluetoothlocaldevice.h>
#include <QObject>
#include <QVariant>
#include <QList>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QBluetoothServiceInfo>

class BLEController : public QObject
{
    Q_OBJECT

public:
    explicit BLEController(QObject* parent = nullptr);

    Q_PROPERTY(bool searchDevicesIconVisible READ getSearchDevicesIconVisible WRITE setSearchDevicesIconVisible NOTIFY searchDevicesIconVisibleChanged)

    Q_INVOKABLE void searchForBLEDevices();
    Q_INVOKABLE void stopSearchForBLEDevices();

private:
    QBluetoothDeviceDiscoveryAgent* m_pBLEDiscoveryAgent;

    bool m_bSearchDevicesIconVisible = false;

private slots:
    // QBluetoothDeviceDiscoveryAgent related
    void AddDevice(const QBluetoothDeviceInfo&);
    void DeviceScanFinished();
    void DeviceScanError(QBluetoothDeviceDiscoveryAgent::Error);

    void setSearchDevicesIconVisible(bool bVisible);
    bool getSearchDevicesIconVisible();

signals:
    void searchDevicesIconVisibleChanged();

};

#endif // BLECONTROLLER_H
