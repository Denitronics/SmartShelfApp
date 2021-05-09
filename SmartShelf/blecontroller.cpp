#include "blecontroller.h"

// ===================================================
BLEController::BLEController(QObject *parent)
// ===================================================
{
    Q_UNUSED(parent)

    // Set searching period to 10 seconds
    m_pBLEDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    m_pBLEDiscoveryAgent->setLowEnergyDiscoveryTimeout(20000);
    connect(m_pBLEDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BLEController::BLEAddDevice);
    connect(m_pBLEDiscoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &BLEController::BLEDeviceScanError);
    connect(m_pBLEDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BLEController::BLEDeviceScanFinished);

    m_pBLEDevicesModel = new BLEDevicesModel(parent);
    m_pShelvesModel = new ShelvesModel(parent);

    BLEDeviceItem::DeclareQML();
    ShelfItemModel::DeclareQML();
    ShelfItem::DeclareQML();
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
    m_pShelvesModel->ClearModel();
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
        m_pShelvesModel->ClearModel();
        m_pBLEController->disconnectFromDevice();
    }
}

// ===================================================
void BLEController::AnalyzeHeaderCharacteristic()
// ===================================================
{
    for (quint8 idx = 0; idx < m_arrBLECharacteristics.size(); idx++)
    {
        if (m_arrBLECharacteristics.at(idx).uuid().toString() == BLE_HEADER_CHARACTERISTIC)
        {
            QByteArray arrHeaderCharacteristicData = m_arrBLECharacteristics.at(idx).value();
            quint8 nDevicesNum = static_cast<quint8>(arrHeaderCharacteristicData.at(0));

            for (quint8 i = 0; i < nDevicesNum; i++)
            {
                m_pShelvesModel->AddShelfItemModel(static_cast<ShelvesModel::ShelfType>(arrHeaderCharacteristicData.at(i * 3 + 1)), arrHeaderCharacteristicData.at(i * 3 + 2),
                                                   arrHeaderCharacteristicData.at(i * 3 + 3));
            }

            break;
        }
    }
}

// ===================================================
void BLEController::DisplayDialogMessage(quint8 nLogType, quint8 nLogMsg)
// ===================================================
{
    bool bOpenMessageDialog = false;

    if (nLogType == LogType::LogType_Info)
    {
        setMsgDialogTitle("Information");
        setMsgDialogIconType("Info");

        if (nLogMsg == LogInfo::Info_SystemOK)
        {
            bOpenMessageDialog = false;
        }
        else if (nLogMsg == LogInfo::Info_ShelfEmpty)
        {
            bOpenMessageDialog = true;
            setMsgDialogText("Shelf is empty!");
        }
    }

    else if (nLogType == LogType::LogType_Warning)
    {
        setMsgDialogTitle("Warning");
        setMsgDialogIconType("Warning");

        if (nLogMsg == LogWarning::Warning_None)
        {
            bOpenMessageDialog = false;
        }
        else if (nLogMsg == LogWarning::Warning_StockAdded)
        {
            bOpenMessageDialog = true;
            setMsgDialogText("Item added to the shelf!");
        }
        else if (nLogMsg == LogWarning::Warning_StockTaken)
        {
            bOpenMessageDialog = true;
            setMsgDialogText("Item removed from the shelf!");
        }
    }

    else if (nLogType == LogType::LogType_Error)
    {
        setMsgDialogTitle("Error");
        setMsgDialogIconType("Error");

        if (nLogMsg == LogError::Error_None)
        {
            bOpenMessageDialog = false;
        }
        else if (nLogMsg == LogError::Error_EEPROM)
        {
            bOpenMessageDialog = true;
            setMsgDialogText("Smart Shelf HW (EEPROM) error!");
        }
    }

    if (bOpenMessageDialog)
    {
        //! Display system information/warning/error
        emit openMessageDialog();
    }
}

// ===================================================
void BLEController::BLEAddDevice(const QBluetoothDeviceInfo &info)
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
void BLEController::BLEDeviceScanFinished()
// ===================================================
{
    setSearchingInProcess(false);
    setSearchDevicesIconVisible(false);
}

// ===================================================
void BLEController::BLEDeviceScanError(QBluetoothDeviceDiscoveryAgent::Error)
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
ShelvesModel *BLEController::shelvesModel()
// ===================================================
{
    return m_pShelvesModel;
}

// ===================================================
void BLEController::setShelvesModel(ShelvesModel *pShelvesModel)
// ===================================================
{
    if (m_pShelvesModel != pShelvesModel)
    {
        m_pShelvesModel = pShelvesModel;
        emit shelvesModelChanged();
    }
}

// ===================================================
void BLEController::setMsgDialogTitle(QString strTitle)
// ===================================================
{
    if (m_strMessageDialogTitle != strTitle)
    {
        m_strMessageDialogTitle = strTitle;
        emit onMsgDialogTitleChanged(m_strMessageDialogTitle);
    }
}

// ===================================================
void BLEController::setMsgDialogText(QString strText)
// ===================================================
{
    if (m_strMessageDialogText != strText)
    {
        m_strMessageDialogText = strText;
        emit onMsgDialogTextChanged(m_strMessageDialogText);
    }
}

// ===================================================
void BLEController::setMsgDialogIconType(QString strIconType)
// ===================================================
{
    if (m_strMessageDialogIconType != strIconType)
    {
        m_strMessageDialogIconType = strIconType;
        emit onMsgDialogIconTypeChanged(m_strMessageDialogIconType);
    }
}

// ===================================================
QString BLEController::msgDialogTitle()
// ===================================================
{
    return m_strMessageDialogTitle;
}

// ===================================================
QString BLEController::msgDialogText()
// ===================================================
{
    return m_strMessageDialogText;
}

// ===================================================
QString BLEController::msgDialogIconType()
// ===================================================
{
    return m_strMessageDialogIconType;
}

// ===================================================
void BLEController::BLEDeviceConnected()
// ===================================================
{
    qDebug() << "Connected to BLE device!";
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
            connect(m_pCurrentBLEService, &QLowEnergyService::characteristicChanged, this, &BLEController::BLECharacteristicValueChanged);
            connect(m_pCurrentBLEService, &QLowEnergyService::characteristicRead, this, &BLEController::BLEReadCharacteristicValue);

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
            m_arrBLECharacteristics = m_pCurrentBLEService->characteristics();

            // Fill the shelves data model
            AnalyzeHeaderCharacteristic();

            for (quint8 idx = 0; idx < m_arrBLECharacteristics.count(); idx++)
            {
                QLowEnergyDescriptor notification = m_arrBLECharacteristics.at(idx).descriptor(
                    QBluetoothUuid::ClientCharacteristicConfiguration);

                if (!notification.isValid())
                {
                    return;
                }

                m_pCurrentBLEService->writeDescriptor(notification, QByteArray::fromHex("0100"));

                if (m_arrBLECharacteristics.at(idx).uuid().toString() == BLE_REMAINING_STOCK_CHAR && m_arrBLECharacteristics.at(idx).isValid())
                {
                    //! Update shelf remaining stock
                    m_pShelvesModel->UpdateShelfItemModel(0, m_arrBLECharacteristics.at(idx).value().at(0));
                }

                else if (m_arrBLECharacteristics.at(idx).uuid().toString() == BLE_LOG_MSG_CHAR && m_arrBLECharacteristics.at(idx).isValid())
                {
                    quint8 nLogType = m_arrBLECharacteristics.at(idx).value().at(0);
                    quint8 nLogMsg  = m_arrBLECharacteristics.at(idx).value().at(1);

                    DisplayDialogMessage(nLogType, nLogMsg);
                }
            }

            setShelfScreenActiveLayout(SHELF_SCREEN_LAYOUT_CONNECTED_BLE);
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
void BLEController::BLECharacteristicValueChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue)
// ===================================================
{
    qDebug() << "Changed characteristic: " << characteristic.uuid().toString();
    qDebug() << "Value: " << newValue;

    if (characteristic.uuid().toString() == BLE_REMAINING_STOCK_CHAR && characteristic.isValid())
    {
        //! Update shelf remaining stock
        m_pShelvesModel->UpdateShelfItemModel(0, newValue.at(0));
    }

    else if (characteristic.uuid().toString() == BLE_LOG_MSG_CHAR && characteristic.isValid())
    {
        quint8 nLogType = newValue.at(0);
        quint8 nLogMsg  = newValue.at(1);

        DisplayDialogMessage(nLogType, nLogMsg);
    }
}

// ===================================================
void BLEController::BLEReadCharacteristicValue(const QLowEnergyCharacteristic &info, const QByteArray &value)
// ===================================================
{
    Q_UNUSED(value)
    Q_UNUSED(info)
}
// ===================================================
