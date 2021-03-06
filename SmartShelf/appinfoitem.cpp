#include "appinfoitem.h"

AppInfoItem::AppInfoItem(QObject* parent) : QObject(parent) {}

void AppInfoItem::DeclareQML()
{
    // code enters here
    qmlRegisterType<AppInfoItem>("Datamodels", 1, 0, "AppInfoItem");
}

void AppInfoItem::setAppInfoType(QString strAppInfoType)
{
    if (strAppInfoType != m_strAppInfoType)
    {
        m_strAppInfoType = strAppInfoType;
        emit appInfoTypeChanged();
    }
}

void AppInfoItem::setAppInfo(QString strAppInfo)
{
    if (strAppInfo != m_strAppInfo)
    {
        m_strAppInfo = strAppInfo;
        emit appInfoChanged();
    }
}

QString AppInfoItem::getAppInfoType()
{
    return m_strAppInfoType;
}

QString AppInfoItem::getAppInfo()
{
    return m_strAppInfo;
}
