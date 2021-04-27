#include "shelfitem.h"

ShelfItem::ShelfItem(QObject *parent) : QObject(parent)
{

}

void ShelfItem::DeclareQML()
{
    qmlRegisterType<ShelfItem>("Datamodels", 1, 0, "ShelfItem");
}

void ShelfItem::setShelfIcon(QString strShelfIcon)
{
    if (m_strShelfIcon != strShelfIcon)
    {
        m_strShelfIcon = strShelfIcon;
        emit shelfIconChanged(m_strShelfIcon);
    }
}

void ShelfItem::setIsItemAvailable(bool bItemAvailable)
{
    if (m_bItemAvailable != bItemAvailable)
    {
        m_bItemAvailable = bItemAvailable;
        emit itemAvailableChanged(m_bItemAvailable);
    }
}

QString ShelfItem::shelfIcon()
{
    return m_strShelfIcon;
}

bool ShelfItem::itemAvailable()
{
    return m_bItemAvailable;
}
