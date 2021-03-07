#include "blecontroller.h"


BLEController::BLEController(QObject *parent)
{
    Q_UNUSED(parent)

    m_pBLEDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    m_pBLEDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);
    connect(m_pBLEDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BLEController::AddDevice);
    connect(m_pBLEDiscoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &BLEController::DeviceScanError);
    connect(m_pBLEDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BLEController::DeviceScanFinished);
}

void BLEController::searchForBLEDevices()
{
    qDebug() << "Start searching for BLE devices ...";
    setSearchDevicesIconVisible(true);
    m_pBLEDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

}

void BLEController::stopSearchForBLEDevices()
{
    qDebug() << "Searching stopped";
    setSearchDevicesIconVisible(false);
    m_pBLEDiscoveryAgent->stop();

}

void BLEController::AddDevice(const QBluetoothDeviceInfo &)
{

}

void BLEController::DeviceScanFinished()
{
    setSearchDevicesIconVisible(false);
}

void BLEController::DeviceScanError(QBluetoothDeviceDiscoveryAgent::Error)
{
    setSearchDevicesIconVisible(false);
}

void BLEController::setSearchDevicesIconVisible(bool bVisible)
{
    if (m_bSearchDevicesIconVisible != bVisible)
    {
        m_bSearchDevicesIconVisible = bVisible;
        emit searchDevicesIconVisibleChanged();
    }
}

bool BLEController::getSearchDevicesIconVisible()
{
    return m_bSearchDevicesIconVisible;
}
