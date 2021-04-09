#pragma once

#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>
#include <QObject>
#include "shelfitem.h"
#include "defines.h"

class ShelvesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ShelvesModel(QObject* parent = nullptr);

    enum AppInfoRoles
    {
        ObjectRole = Qt::UserRole + 1,
        SizeRole
    };

    enum ShelfType
    {
        ShelfType_Drink = 0,
        ShelfType_Snack
    };

    void DeclareQML();
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    void AddShelfItem(ShelfType eShelfType, quint8 nInitialStock);
    void UpdateShelfItem(quint8 index, quint8 nLeftStock);

    void ClearModel();

    protected:
    QHash<int, QByteArray> roleNames() const;

    private:
    QList<ShelfItem*> m_arrSmartShelvesItems;
};

