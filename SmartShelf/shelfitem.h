#ifndef SHELFITEM_H
#define SHELFITEM_H

#include <QObject>
#include <QQmlEngine>
#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>
#include <QObject>

class ShelfItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString shelfIcon READ shelfIcon NOTIFY shelfIconChanged)
    Q_PROPERTY(bool itemAvailable READ itemAvailable NOTIFY itemAvailableChanged)

public:
    explicit ShelfItem(QObject *parent = nullptr);

    static void DeclareQML();

    void setShelfIcon(QString strShelfIcon);
    void setIsItemAvailable(bool bItemAvailable);

    QString shelfIcon();
    bool itemAvailable();

private:
    QString m_strShelfIcon;
    bool m_bItemAvailable;

signals:
    void shelfIconChanged(QString strShelfIconChanged);
    void itemAvailableChanged(bool bItemAvailable);
};

#endif // SHELFITEM_H
