#pragma once

#include <QObject>
#include <QVariant>

class AppInfoItem
{
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)

public:
    AppInfoItem(const QString &strAppInfoType, const QString &vAppInfo);

    QString GetAppInfoType();
    QString GetAppInfo();

private:
    QString m_strAppInfoType = "";
    QString m_strAppInfo;

};


