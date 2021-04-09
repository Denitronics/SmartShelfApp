#include "shelfitem.h"

ShelfItem::ShelfItem(QObject *parent) : QObject(parent) {}


void ShelfItem::DeclareQML()
{
    qmlRegisterType<ShelfItem>("Datamodels", 1, 0, "ShelfItem");
}

QString ShelfItem::shelfIcon()
{
    return m_strShelfIcon;
}

QString ShelfItem::shelfName()
{
    return m_strShelfName;
}

quint8 ShelfItem::initialStock()
{
    return m_nInitialStock;
}

quint8 ShelfItem::leftStock()
{
    return m_nInitialStock;
}

void ShelfItem::setShelfIcon(QString strIcon)
{
    if (m_strShelfIcon != strIcon)
    {
        m_strShelfIcon = strIcon;
        emit shelfIconChanged(m_strShelfIcon);
    }
}

void ShelfItem::setShelfName(QString strShelfName)
{
    if (m_strShelfName != strShelfName)
    {
        m_strShelfName = strShelfName;
        emit shelfNameChanged(m_strShelfName);
    }
}

void ShelfItem::setInitialStock(quint8 nInitialStock)
{
    if (m_nInitialStock != nInitialStock)
    {
        m_nInitialStock = nInitialStock;
        emit initialStockChanged(m_nInitialStock);
    }
}

void ShelfItem::setLeftStock(quint8 nLeftStock)
{
    if (m_nLeftStock != nLeftStock)
    {
        m_nLeftStock = nLeftStock;
        emit initialStockChanged(m_nLeftStock);
    }
}
