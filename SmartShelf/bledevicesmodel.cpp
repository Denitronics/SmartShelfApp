#include "bledevicesmodel.h"


BLEDevicesModel::BLEDevicesModel(QObject* parent) : QAbstractListModel(parent)
{
    // Initialize the model
    beginResetModel();

    for (BLEDeviceItem* pMenuItem : qAsConst(m_arrBLEDeviceItems))
    {
        pMenuItem->deleteLater();
    }
    m_arrBLEDeviceItems.clear();

    endResetModel();
}

void BLEDevicesModel::DeclareQML()
{
    qmlRegisterType<BLEDevicesModel>("Datamodels", 1, 0, "BLEDevicesModel");
}

int BLEDevicesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_arrBLEDeviceItems.count();
}

QVariant BLEDevicesModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_arrBLEDeviceItems.count())
    {
        return QVariant();
    }

    BLEDeviceItem* currentAppInfoItem = m_arrBLEDeviceItems.at(index.row());

    if (role == ObjectRole)
    {
        return QVariant::fromValue(currentAppInfoItem);
    }

    else if (role == SizeRole)
    {
        return m_arrBLEDeviceItems.size();
    }

    return QVariant();
}

bool BLEDevicesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    BLEDeviceItem* pBLEDevice = qvariant_cast<BLEDeviceItem *>(value);

    m_arrBLEDeviceItems.insert(index.row(), pBLEDevice);

    emit dataChanged(index, index);

    return true;
}

void BLEDevicesModel::AddBLEDeviceItem(QString strBLEName, QString strBLEAddress)
{
    bool bDeviceAlreadyDiscovered = false;

    // Check if the device is not already discovered
    for (quint8 idx = 0; idx < m_arrBLEDeviceItems.size(); idx++)
    {
        if (m_arrBLEDeviceItems.at(idx)->getBLEDeviceName() == strBLEName)
        {
            bDeviceAlreadyDiscovered = true;
            break;
        }
    }

    if (!bDeviceAlreadyDiscovered)
    {
        beginInsertRows(QModelIndex(), 0, 0);

        BLEDeviceItem* pCurrentBLEDevice = new BLEDeviceItem(this);
        pCurrentBLEDevice->setBLEDeviceName(strBLEName);
        pCurrentBLEDevice->setBLEDeviceAddress(strBLEAddress);

        m_arrBLEDeviceItems.insert(m_arrBLEDeviceItems.size(), pCurrentBLEDevice);

        endInsertRows();

        emit layoutChanged();
    }
}

void BLEDevicesModel::ClearModel()
{
    beginResetModel();

    for (BLEDeviceItem* pMenuItem : qAsConst(m_arrBLEDeviceItems))
    {
        pMenuItem->deleteLater();
    }
    m_arrBLEDeviceItems.clear();

    endResetModel();
}

QHash<int, QByteArray> BLEDevicesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ObjectRole]   = "object";
    roles[SizeRole]     = "size";
    return roles;
}
