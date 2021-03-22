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
                this, &BLEController::BLEAddService, Qt::ConnectionType::QueuedConnection);
        connect(m_pBLEController, &QLowEnergyController::discoveryFinished,
                this, &BLEController::BLEServiceScanDone, Qt::ConnectionType::QueuedConnection);
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
    qDebug() << "BLE Devices Scanning Error!";
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

    // Scan for services
    m_pBLEController->discoverServices();
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
    //! [les-service-1]
    QString strBLEServiceUUID = uuid.toString();

    if (strBLEServiceUUID == BLE_SERVICE_UUID)
    {
        qDebug() << "Service found!";

        m_pCurrentBLEService = m_pBLEController->createServiceObject(uuid);

        if (!m_pCurrentBLEService) {
            qWarning() << "Cannot create service for uuid";
            return;
        }
    }
}

// ===================================================
void BLEController::BLEServiceScanDone()
// ===================================================
{
    qDebug() << "BLE service state:" << m_pCurrentBLEService->state();

    if (m_pCurrentBLEService)
    {
        if (m_pCurrentBLEService->state() == QLowEnergyService::DiscoveryRequired)
        {
            connect(m_pCurrentBLEService, &QLowEnergyService::stateChanged,
                    this, &BLEController::BLEServiceDetailsDiscovered);
            connect(m_pCurrentBLEService, &QLowEnergyService::characteristicChanged, this, &BLEController::SmartShelfValueChanged);
            m_pCurrentBLEService->discoverDetails();
        }
        else if (m_pCurrentBLEService->state() == QLowEnergyService::ServiceDiscovered)
        {
            BLEServiceDetailsDiscovered(QLowEnergyService::ServiceDiscovered);
        }
    }
}

// ===================================================
void BLEController::BLEServiceDetailsDiscovered(QLowEnergyService::ServiceState newState)
// ===================================================
{
    if (m_pBLEController->error() != QLowEnergyController::Error::NoError)
    {
        qDebug () << "Error: " << m_pBLEController->error();
    }
    if (m_pCurrentBLEService->error() != QLowEnergyService::ServiceError::NoError)
    {
        qDebug () << "Error: " << m_pCurrentBLEService->error();
    }
    qDebug () << "BLE Service new state: " << newState;

    if (newState == QLowEnergyService::DiscoveryRequired)
    {
        m_pCurrentBLEService->discoverDetails();
    }

    else if (newState == QLowEnergyService::ServiceDiscovered)
    {
        if (m_pCurrentBLEService)
        {
            m_arrCharacteristics = m_pCurrentBLEService->characteristics();


            qDebug() << "Characteristics found:";

            for (quint8 idx = 0; idx < m_arrCharacteristics.size(); idx++)
            {
                QByteArray arrValues = m_arrCharacteristics.at(idx).value();
                qDebug() << "Characteristic: " << m_arrCharacteristics.at(idx).name() << " - "<<m_arrCharacteristics.at(idx).uuid() << " - " << m_arrCharacteristics.at(idx).value();
                qDebug() << "Properties: " << m_arrCharacteristics.at(idx).properties();
                //qDebug() << "Descriptor: " << m_arrCharacteristics.at(idx).descriptors();
            }
        }
    }
}

// ===================================================
void BLEController::BLEServiceError(QLowEnergyService::ServiceError error)
// ===================================================
{
    qDebug() << "Service error: " << error;
}

// ===================================================
void BLEController::SmartShelfValueChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue)
// ===================================================
{
    qDebug() << "Characteristic updated!";
    if (characteristic.uuid().toString() == BLE_CHARACTERISTIC_UUID)
    {
        qDebug() << "Characteristic value updated: " << newValue;
    }
}
// ===================================================
