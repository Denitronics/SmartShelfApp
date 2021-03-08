#include "bledeviceitem.h"


BLEDeviceItem::BLEDeviceItem(QObject *parent) : QObject(parent) {}


void BLEDeviceItem::DeclareQML()
{
    qmlRegisterType<BLEDeviceItem>("Datamodels", 1, 0, "BLEDeviceItem");
}

QString BLEDeviceItem::getBLEDeviceName()
{
    return m_strBLEDeviceName;
}

QString BLEDeviceItem::getBLEDeviceAddress()
{
    return m_strBLEDeviceAddress;
}

void BLEDeviceItem::setBLEDeviceName(QString strDeviceName)
{
    if (m_strBLEDeviceName != strDeviceName)
    {
        m_strBLEDeviceName = strDeviceName;
        emit bleDeviceNameChanged();
    }
}

void BLEDeviceItem::setBLEDeviceAddress(QString strDeviceAddress)
{
    if (m_strBLEDeviceAddress != strDeviceAddress)
    {
        m_strBLEDeviceAddress = strDeviceAddress;
        emit bleDeviceAddressChanged();
    }
}
