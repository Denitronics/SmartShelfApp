#pragma once

#include "appinfoitem.h"
#include <QAbstractListModel>
#include <QStringList>

class AppInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AppInfoRoles
    {
        InfoTypeRole = Qt::UserRole + 1,
        InfoRole,
        ObjectRole,
        SizeRole
    };

    explicit AppInfoModel(QObject* parent = nullptr);

    void DeclareQML();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<AppInfoItem*> m_arrAppInfoItems;

    const QString m_strJsonFileDir = ":/data/appInfo.json";
};
