#include "shelfitemmodel.h"

ShelfItemModel::ShelfItemModel(QObject *parent) : QAbstractListModel(parent)
{
}

void ShelfItemModel::DeclareQML()
{
    qmlRegisterType<ShelfItemModel>("Datamodels", 1, 0, "ShelfItemModel");
}

void ShelfItemModel::FillModel(quint8 nInitialStock, quint8 nLeftStock)
{
    beginInsertRows(QModelIndex(), 0, 0);

    for (quint8 idx = 0; idx < nInitialStock; idx++)
    {
        ShelfItem* pCurrentItem = new ShelfItem(this);

        if (shelfName() == QLatin1String("Drinks"))
        {
            pCurrentItem->setShelfIcon(SHELF_DRINK_ITEM_ICON);
        }
        else
        {
            pCurrentItem->setShelfIcon(SHELF_CHIPS_ITEM_ICON);
        }

        if (idx < nLeftStock)
        {
            pCurrentItem->setIsItemAvailable(true);
        }
        else
        {
            pCurrentItem->setIsItemAvailable(false);
        }

        m_arrSmartShelfItems.insert(m_arrSmartShelfItems.size(), pCurrentItem);
    }

    endInsertRows();
    emit layoutChanged();
}

void ShelfItemModel::UpdateModel(quint8 nLeftStock)
{
    beginResetModel();

    for (quint8 idx = 0; idx < m_arrSmartShelfItems.size(); idx++)
    {
        if (idx < nLeftStock)
        {
            m_arrSmartShelfItems.at(idx)->setIsItemAvailable(true);
        }
        else
        {
            m_arrSmartShelfItems.at(idx)->setIsItemAvailable(false);
        }
    }

    endResetModel();
}

int ShelfItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_arrSmartShelfItems.count();
}

QVariant ShelfItemModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_arrSmartShelfItems.count())
    {
        return QVariant();
    }

    ShelfItem* currentShelfItem= m_arrSmartShelfItems.at(index.row());

    if (role == ObjectRole)
    {
        return QVariant::fromValue(currentShelfItem);
    }

    else if (role == SizeRole)
    {
        return m_arrSmartShelfItems.size();
    }

    return QVariant();
}

QHash<int, QByteArray> ShelfItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ObjectRole]   = "object";
    roles[SizeRole]     = "size";
    return roles;
}

QString ShelfItemModel::shelfIcon()
{
    return m_strShelfIcon;
}

QString ShelfItemModel::shelfName()
{
    return m_strShelfName;
}

void ShelfItemModel::setShelfIcon(QString strIcon)
{
    if (m_strShelfIcon != strIcon)
    {
        m_strShelfIcon = strIcon;
        emit shelfIconChanged(m_strShelfIcon);
    }
}

void ShelfItemModel::setShelfName(QString strShelfName)
{
    if (m_strShelfName != strShelfName)
    {
        m_strShelfName = strShelfName;
        emit shelfNameChanged(m_strShelfName);
    }
}

void ShelfItemModel::setLeftStock(quint8 nLeftStock)
{
    if (m_nLeftStock != nLeftStock)
    {
        m_nLeftStock = nLeftStock;
        //emit leftStockChanged(m_nLeftStock);
    }
}

quint8 ShelfItemModel::getInitialItemsCount()
{
    return m_arrSmartShelfItems.size();
}
