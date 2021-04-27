#include "shelvesmodel.h"


ShelvesModel::ShelvesModel(QObject* parent) : QAbstractListModel(parent)
{
    // Initialize the model
    beginResetModel();

    for (ShelfItemModel* pItem : qAsConst(m_arrSmartShelvesItemsModels))
    {
        pItem->deleteLater();
    }
    m_arrSmartShelvesItemsModels.clear();

    endResetModel();
}

void ShelvesModel::DeclareQML()
{
    qmlRegisterType<ShelvesModel>("Datamodels", 1, 0, "ShelvesModel");
}

int ShelvesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_arrSmartShelvesItemsModels.count();
}

QVariant ShelvesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_arrSmartShelvesItemsModels.count())
    {
        return QVariant();
    }

    ShelfItemModel* currentShelfItemModel = m_arrSmartShelvesItemsModels.at(index.row());

    if (role == ObjectRole)
    {
        return QVariant::fromValue(currentShelfItemModel);
    }

    else if (role == SizeRole)
    {
        return m_arrSmartShelvesItemsModels.size();
    }

    return QVariant();
}

void ShelvesModel::AddShelfItemModel(ShelvesModel::ShelfType eShelfType, quint8 nInitialStock, quint8 nLeftStock)
{
    Q_UNUSED(nInitialStock);

    beginInsertRows(QModelIndex(), 0, 0);

    ShelfItemModel* pCurrentShelf = new ShelfItemModel(this->parent());

    if (eShelfType == ShelfType::ShelfType_Drink)
    {
        pCurrentShelf->setShelfIcon(SHELF_DRINK_ICON);
        pCurrentShelf->setShelfName("Drinks");
    }
    else if (eShelfType == ShelfType::ShelfType_Snack)
    {
        pCurrentShelf->setShelfIcon(SHELF_SNACK_ICON);
        pCurrentShelf->setShelfName("Snacks");
    }
    else
    {
        pCurrentShelf->setShelfIcon(SHELF_UNKNOWN_ICON);
    }

    pCurrentShelf->FillModel(nInitialStock, nLeftStock);

    m_arrSmartShelvesItemsModels.insert(m_arrSmartShelvesItemsModels.size(), pCurrentShelf);

    endInsertRows();

    emit layoutChanged();
}

void ShelvesModel::UpdateShelfItemModel(quint8 index, quint8 nLeftStock)
{    
    if (index >= 0 && index < m_arrSmartShelvesItemsModels.count())
    {
        ShelfItemModel* pUpdatedShelf = m_arrSmartShelvesItemsModels.at(index);

        beginResetModel();
        pUpdatedShelf->UpdateModel(nLeftStock);
        endResetModel();

        qDebug() << "Item: " << index << "Left stock: " << nLeftStock;
    }
}

void ShelvesModel::ClearModel()
{
    beginResetModel();

    for (ShelfItemModel* pShelfItemModel : qAsConst(m_arrSmartShelvesItemsModels))
    {
        pShelfItemModel->deleteLater();
    }
    m_arrSmartShelvesItemsModels.clear();

    endResetModel();
}

QHash<int, QByteArray> ShelvesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ObjectRole]   = "object";
    roles[SizeRole]     = "size";
    return roles;
}
