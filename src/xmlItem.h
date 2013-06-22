#ifndef XMLITEM_H
#define XMLITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QByteArray>
#include <QString>

class XmlItem : public QObject
{
    Q_OBJECT
public:
    explicit XmlItem(QObject *parent = 0) : QObject(parent) {}
    virtual QVariant data(int role) const = 0;
    virtual bool setData (const QVariant &value, int role) = 0;
    virtual QHash<int, QByteArray> roleNames() = 0;
    virtual QString xmlTag() = 0;
};

#endif // XMLITEM_H
