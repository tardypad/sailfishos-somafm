#include "xmlItem.h"

XmlItem::XmlItem(QObject *parent) :
    QObject(parent),
    m_isClone(false),
    m_isBookmark(false)
{
}


QVariant XmlItem::data(int role) const
{
    switch(role) {
    case IsCloneRole:
        return isClone();
    case IsBookmarkRole:
        return isBookmark();
    }

    return QVariant();
}

bool XmlItem::setData (const QVariant &value, int role)
{
    switch(role) {
    case IsCloneRole:
        setIsClone(value.toBool());
        return true;
    case IsBookmarkRole:
        setIsBookmark(value.toBool());
        return true;
    }

    return false;
}

QHash<int, QByteArray> XmlItem::roleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[IsCloneRole] = "isClone";
    roleNames[IsBookmarkRole] = "isBookmark";

    return roleNames;
}

XmlItem* XmlItem::clone()
{
    return cloneRoles(roleNames());
}

XmlItem* XmlItem::cloneRoles(QHash<int, QByteArray> roles)
{
    QHashIterator<int, QByteArray> iterator(roles);
    XmlItem* newXmlItem = create();
    int role;
    QVariant value;

    while (iterator.hasNext()) {
         iterator.next();
         role = iterator.key();
         value = data(role);
         newXmlItem->setData(value, role);
     }

    newXmlItem->setData(true, XmlItem::IsCloneRole);

    return newXmlItem;
}
