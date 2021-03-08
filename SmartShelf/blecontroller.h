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
#include <bledevicesmodel.h>
#include <bledeviceitem.h>

class BLEController : public QObject
{
    Q_OBJECT

public:
    explicit BLEController(QObject* parent = nullptr);

    Q_PROPERTY(bool searchDevicesIconVisible READ getSearchDevicesIconVisible WRITE setSearchDevicesIconVisible NOTIFY searchDevicesIconVisibleChanged)
    Q_PROPERTY(BLEDevicesModel* bleDevicesModel READ getBLEDevicesModel WRITE setBLEDevicesModel NOTIFY onBLEDevicesModelChanged)

    Q_INVOKABLE void searchForBLEDevices();
    Q_INVOKABLE void stopSearchForBLEDevices();

private:
    QBluetoothDeviceDiscoveryAgent* m_pBLEDiscoveryAgent;
    QLowEnergyController *m_pBLEController = nullptr;

    BLEDevicesModel* m_pBLEDevicesModel = nullptr;

    bool m_bSearchDevicesIconVisible = false;

private slots:
    // QBluetoothDeviceDiscoveryAgent related
    void AddDevice(const QBluetoothDeviceInfo&info);
    void DeviceScanFinished();
    void DeviceScanError(QBluetoothDeviceDiscoveryAgent::Error);

    void setSearchDevicesIconVisible(bool bVisible);
    void setBLEDevicesModel(BLEDevicesModel * pBLEDevicesModel);
    bool getSearchDevicesIconVisible();
    BLEDevicesModel* getBLEDevicesModel();

signals:
    void searchDevicesIconVisibleChanged();
    void onBLEDevicesModelChanged();

};

#endif // BLECONTROLLER_H
