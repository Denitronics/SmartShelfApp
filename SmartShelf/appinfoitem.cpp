#include "appinfoitem.h"

AppInfoItem::AppInfoItem(const QString &strAppInfoType, const QString &strAppInfo)
{
    m_strAppInfoType = strAppInfoType;
    m_strAppInfo = strAppInfo;
}

QString AppInfoItem::GetAppInfoType()
{
    return m_strAppInfoType;
}

QString AppInfoItem::GetAppInfo()
{
    return m_strAppInfo;
}

