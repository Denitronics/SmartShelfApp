#ifndef BLECONTROLLER_H
#define BLECONTROLLER_H

#include <QObject>
#include <QtDebug>
#include <qbluetoothlocaldevice.h>
#include <QObject>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QBluetoothServiceInfo>
#include <bledevicesmodel.h>
#include <bledeviceitem.h>
#include <QTimer>
#include <shelvesmodel.h>
#include <shelfitemmodel.h>
#include "defines.h"


class BLEController : public QObject
{
    Q_OBJECT

public:
    explicit BLEController(QObject* parent = nullptr);

    Q_PROPERTY(bool searchDevicesIconVisible READ getSearchDevicesIconVisible WRITE setSearchDevicesIconVisible NOTIFY searchDevicesIconVisibleChanged)
    Q_PROPERTY(bool searchingInProcess READ getSearchingInProcess WRITE setSearchingInProcess NOTIFY searchingInProcessChanged)
    Q_PROPERTY(quint8 shelfScreenActiveLayout READ shelfScreenActiveLayout WRITE setShelfScreenActiveLayout NOTIFY shelfScreenActiveLayoutChanged)
    Q_PROPERTY(BLEDevicesModel* bleDevicesModel READ getBLEDevicesModel WRITE setBLEDevicesModel NOTIFY onBLEDevicesModelChanged)
    Q_PROPERTY(ShelvesModel* shelvesModel READ shelvesModel NOTIFY shelvesModelChanged)

    Q_INVOKABLE void searchForBLEDevices();
    Q_INVOKABLE void stopSearchForBLEDevices();
    Q_INVOKABLE void connectToBLEDevice(quint8 nBLEDeviceIndex);
    Q_INVOKABLE void disconnectFromBLEDevice();

private:
    void AnalyzeHeaderCharacteristic();

    // Data models
    BLEDevicesModel* m_pBLEDevicesModel = nullptr;
    ShelvesModel* m_pShelvesModel       = nullptr;

    // BLE related members
    QLowEnergyController *m_pBLEController = nullptr;
    QBluetoothDeviceDiscoveryAgent* m_pBLEDiscoveryAgent;
    QList<QBluetoothDeviceInfo> m_arrBLEFoundDevices;
    QBluetoothDeviceInfo m_oCurrentBLEConnectedDevice;
    QLowEnergyService* m_pCurrentBLEService = nullptr;
    QList<QLowEnergyService *> m_arrBLEServices;
    QList<QLowEnergyCharacteristic> m_arrBLECharacteristics;

    bool m_bSearchDevicesIconVisible = false;
    bool m_bSearchInProcess          = false;
    quint8 m_nShelfScreenActiveLayout = SHELF_SCREEN_LAYOUT_SEARCH_BLE;

private slots:

    void BLEAddDevice(const QBluetoothDeviceInfo&info);
    void BLEDeviceScanFinished();
    void BLEDeviceScanError(QBluetoothDeviceDiscoveryAgent::Error);

    void setSearchDevicesIconVisible(bool bVisible);
    void setShelfScreenActiveLayout(quint8 nLayout);
    void setSearchingInProcess(bool bSearchInProcess);
    void setBLEDevicesModel(BLEDevicesModel * pBLEDevicesModel);
    bool getSearchDevicesIconVisible();
    bool getSearchingInProcess();
    quint8 shelfScreenActiveLayout();
    BLEDevicesModel* getBLEDevicesModel();
    ShelvesModel* shelvesModel();
    void setShelvesModel(ShelvesModel* pShelvesModel);

    void BLEDeviceConnected();
    void BLEDeviceDisconnected();
    void BLEDeviceErrorReceived(QLowEnergyController::Error eError);
    void BLEAddService(const QBluetoothUuid &uuid);
    void BLEServiceScanDone();

    // QLowEnergyService related
    void BLEServiceDetailsDiscovered(QLowEnergyService::ServiceState newState);
    void BLEServiceError(QLowEnergyService::ServiceError error);

    void BLECharacteristicValueChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void BLEReadCharacteristicValue(const QLowEnergyCharacteristic &info, const QByteArray &value);

signals:
    void searchDevicesIconVisibleChanged();
    void onBLEDevicesModelChanged();
    void shelvesModelChanged();
    void shelfScreenActiveLayoutChanged();
    void searchingInProcessChanged();
};

#endif // BLECONTROLLER_H
