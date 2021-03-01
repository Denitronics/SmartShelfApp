#pragma once

#include <QAbstractListModel>
#include <QStringList>
#include "appinfoitem.h"

class AppInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AppInfoRoles {
        InfoTypeRole = Qt::UserRole + 1,
        InfoRole
    };

    AppInfoModel(QObject *parent = 0);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<AppInfoItem> m_arrAppInfoItems;

    const QString m_strJsonFileDir = ":/data/appInfo.json";

};

