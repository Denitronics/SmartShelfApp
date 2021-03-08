#pragma once

#include "bledeviceitem.h"
#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>
#include <QObject>

class BLEDevicesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AppInfoRoles
    {
        ObjectRole = Qt::UserRole + 1,
        SizeRole
    };

    explicit BLEDevicesModel(QObject* parent = nullptr);

    void DeclareQML();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    void AddBLEDeviceItem(QString strBLEName, QString strBLEAddress);
    void ClearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<BLEDeviceItem*> m_arrBLEDeviceItems;

};
