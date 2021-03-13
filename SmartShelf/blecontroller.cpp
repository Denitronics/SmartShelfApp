#include "blecontroller.h"

// ===================================================
BLEController::BLEController(QObject *parent)
// ===================================================
{
    Q_UNUSED(parent)

    // Set searching period to 10 seconds
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

// ===================================================
void BLEController::searchForBLEDevices()
// ===================================================
{
    qDebug() << "Start searching for BLE devices ...";
    m_arrBLEFoundDevices.clear();
    setSearchDevicesIconVisible(true);
    setSearchingInProcess(true);
    m_pBLEDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

    m_pBLEDevicesModel->ClearModel();
}

// ===================================================
void BLEController::stopSearchForBLEDevices()
// ===================================================
{
    qDebug() << "Searching stopped";
    setSearchingInProcess(false);
    setSearchDevicesIconVisible(false);
    m_pBLEDiscoveryAgent->stop();
}

// ===================================================
void BLEController::connectToBLEDevice(quint8 nBLEDeviceIndex)
// ===================================================
{
    // get the BLE device by the passed index
    m_oCurrentBLEConnectedDevice = m_arrBLEFoundDevices.at(nBLEDeviceIndex);

    if (!m_oCurrentBLEConnectedDevice.isValid())
    {
        qWarning() << "Not a valid device";
        return;
    }

    if (m_pBLEController)
    {
        m_pBLEController->disconnectFromDevice();
        delete m_pBLEController;
        m_pBLEController = nullptr;
    }

    //! [les-controller-1]
    if (!m_pBLEController) {
        // Connecting signals and slots for connecting to LE services.
        m_pBLEController = QLowEnergyController::createCentral(m_oCurrentBLEConnectedDevice);

        connect(m_pBLEController, &QLowEnergyController::connected,
                this, &BLEController::BLEDeviceConnected);
        connect(m_pBLEController, QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error),
                this, &BLEController::BLEDeviceErrorReceived);
        connect(m_pBLEController, &QLowEnergyController::disconnected,
                this, &BLEController::BLEDeviceDisconnected);
        connect(m_pBLEController, &QLowEnergyController::serviceDiscovered,
                this, &BLEController::BLEAddService);
        connect(m_pBLEController, &QLowEnergyController::discoveryFinished,
                this, &BLEController::BLEServiceScanDone);
    }

    setSearchDevicesIconVisible(true);
    m_pBLEController->setRemoteAddressType(QLowEnergyController::PublicAddress);
    m_pBLEController->connectToDevice();
}

// ===================================================
void BLEController::disconnectFromBLEDevice()
// ===================================================
{
    if (m_pBLEController->state() != QLowEnergyController::UnconnectedState)
    {
        setSearchDevicesIconVisible(true);
        m_arrBLEFoundDevices.clear();
        m_pBLEDevicesModel->ClearModel();
        m_pBLEController->disconnectFromDevice();
    }
}

// ===================================================
void BLEController::AddDevice(const QBluetoothDeviceInfo &info)
// ===================================================
{
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        bool bDeviceFound = false;
        qDebug() << ("Last device added: " + info.name());

        for (quint8 i = 0; i < m_arrBLEFoundDevices.size(); i++)
        {
            if (m_arrBLEFoundDevices.at(i).name() == info.name())
            {
                bDeviceFound = true;
                break;
            }
        }

        if (!bDeviceFound)
        {
            m_arrBLEFoundDevices.append(info);
            m_pBLEDevicesModel->AddBLEDeviceItem(info.name(), info.address().toString());
        }
    }
}

// ===================================================
void BLEController::DeviceScanFinished()
// ===================================================
{
    setSearchingInProcess(false);
    setSearchDevicesIconVisible(false);
}

// ===================================================
void BLEController::DeviceScanError(QBluetoothDeviceDiscoveryAgent::Error)
// ===================================================
{
    setSearchingInProcess(false);
    setSearchDevicesIconVisible(false);
}

// ===================================================
void BLEController::setSearchDevicesIconVisible(bool bVisible)
// ===================================================
{
    if (m_bSearchDevicesIconVisible != bVisible)
    {
        m_bSearchDevicesIconVisible = bVisible;
        emit searchDevicesIconVisibleChanged();
    }
}

// ===================================================
void BLEController::setShelfScreenActiveLayout(quint8 nLayout)
// ===================================================
{
    if (m_nShelfScreenActiveLayout != nLayout)
    {
        m_nShelfScreenActiveLayout = nLayout;
        emit shelfScreenActiveLayoutChanged();
    }
}

// ===================================================
void BLEController::setSearchingInProcess(bool bSearchInProcess)
// ===================================================
{
    if (m_bSearchInProcess != bSearchInProcess)
    {
        m_bSearchInProcess = bSearchInProcess;
        emit searchingInProcessChanged();
    }
}

// ===================================================
void BLEController::setBLEDevicesModel(BLEDevicesModel *pBLEDevicesModel)
// ===================================================
{
    if (pBLEDevicesModel != m_pBLEDevicesModel)
    {
        m_pBLEDevicesModel = pBLEDevicesModel;
        emit onBLEDevicesModelChanged();
    }
}

// ===================================================
bool BLEController::getSearchDevicesIconVisible()
// ===================================================
{
    return m_bSearchDevicesIconVisible;
}

// ===================================================
bool BLEController::getSearchingInProcess()
// ===================================================
{
    return m_bSearchInProcess;
}

// ===================================================
quint8 BLEController::shelfScreenActiveLayout()
// ===================================================
{
    return m_nShelfScreenActiveLayout;
}

// ===================================================
BLEDevicesModel *BLEController::getBLEDevicesModel()
// ===================================================
{
    return m_pBLEDevicesModel;
}

// ===================================================
void BLEController::BLEDeviceConnected()
// ===================================================
{
    setSearchingInProcess(false);
    setSearchDevicesIconVisible(false);
    qDebug() << "Connected to BLE device!";
    setShelfScreenActiveLayout(SHELF_SCREEN_LAYOUT_CONNECTED_BLE);
}

// ===================================================
void BLEController::BLEDeviceDisconnected()
// ===================================================
{
    setSearchingInProcess(false);
    setSearchDevicesIconVisible(false);
    qDebug() << "Disconnected from BLE device!";
    setShelfScreenActiveLayout(SHELF_SCREEN_LAYOUT_SEARCH_BLE);
}

// ===================================================
void BLEController::BLEDeviceErrorReceived(QLowEnergyController::Error eError)
// ===================================================
{
    setSearchingInProcess(false);
    setSearchDevicesIconVisible(false);
    Q_UNUSED(eError);
}

// ===================================================
void BLEController::BLEAddService(const QBluetoothUuid &uuid)
// ===================================================
{
    Q_UNUSED(uuid);
}

// ===================================================
void BLEController::BLEServiceScanDone()
// ===================================================
{

}
// ===================================================