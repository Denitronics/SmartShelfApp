#pragma once

#include <QAbstractListModel>
#include <QJsonObject>
#include <QObject>
#include <QQmlEngine>
#include <QVariant>

class AppInfoItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString appInfoType READ getAppInfoType WRITE setAppInfoType NOTIFY appInfoTypeChanged)
    Q_PROPERTY(QString appInfo READ getAppInfo WRITE setAppInfo NOTIFY appInfoChanged)

    QML_ELEMENT

public:
    ~AppInfoItem() {}

    explicit AppInfoItem(QObject* parent = nullptr);

    static void DeclareQML();

    QString getAppInfoType();
    QString getAppInfo();

    void setAppInfoType(QString strAppInfoType);
    void setAppInfo(QString strAppInfo);

signals:
    void appInfoTypeChanged();
    void appInfoChanged();

private:
    QString m_strAppInfoType = "";
    QString m_strAppInfo;
};
