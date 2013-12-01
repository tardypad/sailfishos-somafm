#include "Support.h"

#include <QDebug>

Support::Support(QObject *parent) :
    XmlItem(parent),
    m_content(""),
    m_location("")
{
}

QHash<int, QByteArray> Support::roleNames()
{
    QHash<int, QByteArray> roleNames = XmlItem::roleNames();

    roleNames[ContentRole] = "content";
    roleNames[LocationRole] = "location";

    return roleNames;
}

QVariant Support::data(int role) const
{
    switch(role) {
    case ContentRole:
        return content();
    case LocationRole:
        return location();
    }

    return XmlItem::data(role);
}

bool Support::setData(const QVariant &value, int role)
{
    switch(role) {
    case ContentRole:
        setContent(value.toString());
        return true;
    case LocationRole:
        setLocation(value.toUrl());
        return true;
    }

    return XmlItem::setData(value, role);
}

XmlItem* Support::create()
{
    return new Support();
}
