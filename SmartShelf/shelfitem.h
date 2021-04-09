#pragma once

#include "QObject"
#include <QQmlEngine>


class ShelfItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString shelfIcon READ shelfIcon NOTIFY shelfIconChanged)
    Q_PROPERTY(QString shelfName READ shelfName NOTIFY shelfNameChanged)
    Q_PROPERTY(quint8 initialStock READ initialStock NOTIFY initialStockChanged)
    Q_PROPERTY(quint8 leftStock READ leftStock NOTIFY leftStockChanged)

public:
    explicit ShelfItem(QObject* parent = nullptr);

    static void DeclareQML();
    QString shelfIcon();
    QString shelfName();
    quint8 initialStock();
    quint8 leftStock();
    void setShelfIcon(QString strIcon);
    void setShelfName(QString strShelfName);
    void setInitialStock(quint8 nInitialStock);
    void setLeftStock(quint8 nLeftStock);

private:
    QString m_strShelfIcon  = "";
    QString m_strShelfName  = "";
    quint8  m_nInitialStock = 0;
    quint8  m_nLeftStock    = 0;

signals:
    void shelfIconChanged(QString strShelfIcon);
    void initialStockChanged(quint8 nInitialStock);
    void leftStockChanged(quint8 nLeftStock);
    void shelfNameChanged(QString strShelfName);
};

