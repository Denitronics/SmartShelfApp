#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>
#include <QObject>
#include "shelfitem.h"
#include "defines.h"


class ShelfItemModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString shelfIcon READ shelfIcon NOTIFY shelfIconChanged)
    Q_PROPERTY(QString shelfName READ shelfName NOTIFY shelfNameChanged)

public:
    explicit ShelfItemModel(QObject* parent = nullptr);

    enum AppInfoRoles
    {
        ObjectRole = Qt::UserRole + 1,
        SizeRole
    };

    static void DeclareQML();
    void FillModel(quint8 nInitialStock, quint8 nLeftStock);
    void UpdateModel(quint8 nLeftStock);

    QString shelfIcon();
    QString shelfName();

    quint8 leftStock();
    void setShelfIcon(QString strIcon);
    void setShelfName(QString strShelfName);

    void setLeftStock(quint8 nLeftStock);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE quint8 getInitialItemsCount();

private:

    QString m_strShelfIcon  = "";
    QString m_strShelfName  = "";

    quint8  m_nLeftStock    = 0;

    QList<ShelfItem*> m_arrSmartShelfItems;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:
    void shelfIconChanged(QString strShelfIcon);
    void shelfNameChanged(QString strShelfName);
};

