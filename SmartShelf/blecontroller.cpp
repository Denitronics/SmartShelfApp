#include "blecontroller.h"


BLEController::BLEController(QObject *parent)
{
    Q_UNUSED(parent)

    m_pBLEDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    m_pBLEDiscoveryAgent->setLowEnergyDiscoveryTimeout(10000);
    connect(m_pBLEDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BLEController::AddDevice);
    connect(m_pBLEDiscoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &BLEController::DeviceScanError);
    connect(m_pBLEDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BLEController::DeviceScanFinished);

    m_pBLEDevicesModel = new BLEDevicesModel(parent);

    BLEDeviceItem::DeclareQML();
}

void BLEController::searchForBLEDevices()
{
    qDebug() << "Start searching for BLE devices ...";
    setSearchDevicesIconVisible(true);
    m_pBLEDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);


    m_pBLEDevicesModel->ClearModel();
}

void BLEController::stopSearchForBLEDevices()
{
    qDebug() << "Searching stopped";
    setSearchDevicesIconVisible(false);
    m_pBLEDiscoveryAgent->stop();
}

void BLEController::AddDevice(const QBluetoothDeviceInfo &info)
{
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        qDebug() << ("Last device added: " + info.name());
        m_pBLEDevicesModel->AddBLEDeviceItem(info.name(), info.address().toString());
    }
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

void BLEController::setBLEDevicesModel(BLEDevicesModel *pBLEDevicesModel)
{
    if (pBLEDevicesModel != m_pBLEDevicesModel)
    {
        m_pBLEDevicesModel = pBLEDevicesModel;
        emit onBLEDevicesModelChanged();
    }
}

bool BLEController::getSearchDevicesIconVisible()
{
    return m_bSearchDevicesIconVisible;
}

BLEDevicesModel *BLEController::getBLEDevicesModel()
{
    return m_pBLEDevicesModel;
}
