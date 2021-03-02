#include "appinfomodel.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

AppInfoModel::AppInfoModel(QObject* parent) : QAbstractListModel(parent)
{
    // Get the data from .json file
    QString strJsonFile;
    QFile oJsonFile;
    oJsonFile.setFileName(m_strJsonFileDir);
    oJsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    strJsonFile = oJsonFile.readAll();
    oJsonFile.close();

    QJsonDocument oJsonDoc    = QJsonDocument::fromJson(strJsonFile.toUtf8());
    QJsonObject oJsonObject   = oJsonDoc.object();
    QJsonValue oJsonFileValue = oJsonObject.value("info");
    QJsonArray arrAppInfo     = oJsonFileValue.toArray();

    // fill the model
    beginResetModel();

    for (AppInfoItem* pMenuItem : m_arrAppInfoItems)
    {
        pMenuItem->deleteLater();
    }
    m_arrAppInfoItems.clear();

    for (quint8 i = 0; i < arrAppInfo.size(); i++)
    {
        QJsonObject currentAppInfo       = arrAppInfo.at(i).toObject();
        AppInfoItem* pCurrentAppInfoItem = new AppInfoItem(this, currentAppInfo.value("name").toString(), currentAppInfo.value("value").toString());
        m_arrAppInfoItems.insert(i, pCurrentAppInfoItem);
    }
    endResetModel();
}


int AppInfoModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_arrAppInfoItems.count();
}

QVariant AppInfoModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_arrAppInfoItems.count())
    {
        return QVariant();
    }

    AppInfoItem* currentAppInfoItem = m_arrAppInfoItems.at(index.row());

    if (role == InfoTypeRole)
    {
        return currentAppInfoItem->GetAppInfoType();
    }

    else if (role == InfoRole)
    {
        return currentAppInfoItem->GetAppInfo();
    }

    else if (role == ObjectRole)
    {
        return QVariant::fromValue(currentAppInfoItem);
    }

    return QVariant();
}

QHash<int, QByteArray> AppInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[InfoTypeRole] = "type";
    roles[InfoRole]     = "value";
    return roles;
}
