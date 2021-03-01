#include "appinfomodel.h"
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>

AppInfoModel::AppInfoModel(QObject *parent) : QAbstractListModel(parent)
{
    // Get the data from .json file
    QString strJsonFile;
    QFile oJsonFile;
    oJsonFile.setFileName(m_strJsonFileDir);
    oJsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    strJsonFile = oJsonFile.readAll();
    oJsonFile.close();

    QJsonDocument oJsonDoc  = QJsonDocument::fromJson(strJsonFile.toUtf8());
    QJsonObject oJsonObject = oJsonDoc.object();
    QJsonArray arrJson = oJsonObject.value(QLatin1String("info"));
    //QJsonValue value = sett2.value(QString("info"))
    qWarning() << arrJson.value("info");
}

int AppInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_arrAppInfoItems.count();
}

QVariant AppInfoModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_arrAppInfoItems.count())
    {
        return QVariant();
    }

    AppInfoItem currentAppInfoItem = m_arrAppInfoItems.at(index.row());

    if (role == InfoTypeRole)
    {
        return currentAppInfoItem.GetAppInfoType();
    }

    else if (role == InfoRole)
    {
        return currentAppInfoItem.GetAppInfo();
    }

    return QVariant();
}

QHash<int, QByteArray> AppInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[InfoTypeRole] = "type";
    roles[InfoRole] = "value";
    return roles;
}
