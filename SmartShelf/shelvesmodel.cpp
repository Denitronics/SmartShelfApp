#include "shelvesmodel.h"


ShelvesModel::ShelvesModel(QObject* parent) : QAbstractListModel(parent)
{
    // Initialize the model
    beginResetModel();

    for (ShelfItem* pItem : qAsConst(m_arrSmartShelvesItems))
    {
        pItem->deleteLater();
    }
    m_arrSmartShelvesItems.clear();

    endResetModel();
}

void ShelvesModel::DeclareQML()
{
    qmlRegisterType<ShelvesModel>("Datamodels", 1, 0, "ShelvesModel");
}

int ShelvesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_arrSmartShelvesItems.count();
}

QVariant ShelvesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_arrSmartShelvesItems.count())
    {
        return QVariant();
    }

    ShelfItem* currentShelfItem = m_arrSmartShelvesItems.at(index.row());

    if (role == ObjectRole)
    {
        return QVariant::fromValue(currentShelfItem);
    }

    else if (role == SizeRole)
    {
        return m_arrSmartShelvesItems.size();
    }

    return QVariant();
}

void ShelvesModel::AddShelfItem(ShelvesModel::ShelfType eShelfType, quint8 nInitialStock)
{
    Q_UNUSED(nInitialStock);

    beginInsertRows(QModelIndex(), 0, 0);

    ShelfItem* pCurrentShelf = new ShelfItem(this);

    if (eShelfType == ShelfType::ShelfType_Drink)
    {
        pCurrentShelf->setShelfIcon(SHELF_DRINK_ICON);
    }
    else if (eShelfType == ShelfType::ShelfType_Snack)
    {
        pCurrentShelf->setShelfIcon(SHELF_SNACK_ICON);
    }
    else
    {
        pCurrentShelf->setShelfIcon(SHELF_UNKNOWN_ICON);
    }

    pCurrentShelf->setInitialStock(nInitialStock);

    m_arrSmartShelvesItems.insert(m_arrSmartShelvesItems.size(), pCurrentShelf);

    endInsertRows();

    emit layoutChanged();
}

void ShelvesModel::UpdateShelfItem(quint8 index, quint8 nLeftStock)
{
    if (index >= 0 && index < m_arrSmartShelvesItems.count())
    {
        beginResetModel();
        m_arrSmartShelvesItems.at(index)->setLeftStock(nLeftStock);
        endResetModel();

        qDebug() << "Item: " << index << "Left stock: " << nLeftStock;
    }
}

void ShelvesModel::ClearModel()
{
    beginResetModel();

    for (ShelfItem* pShelfItem : qAsConst(m_arrSmartShelvesItems))
    {
        pShelfItem->deleteLater();
    }
    m_arrSmartShelvesItems.clear();

    endResetModel();
}

QHash<int, QByteArray> ShelvesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ObjectRole]   = "object";
    roles[SizeRole]     = "size";
    return roles;
}
