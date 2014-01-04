#include "XmlItem.h"

#include <QDebug>

XmlItem::XmlItem(QObject *parent) :
    QObject(parent),
    m_isClone(false),
    m_isBookmark(false),
    m_bookmarkDate(QDateTime())
{
}


QVariant XmlItem::data(int role) const
{
    switch(role) {
    case IsCloneRole:
        return isClone();
    case IsBookmarkRole:
        return isBookmark();
    case BookmarkDateRole:
        return bookmarkDate();
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
    case BookmarkDateRole:
        setBookmarkDate(value.toDateTime());
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

QHash<int, QByteArray> XmlItem::bookmarkRoleNames()
{
    QHash<int, QByteArray> bookmarkRoleNames;
    bookmarkRoleNames[BookmarkDateRole] = "bookmarkDate";

    return bookmarkRoleNames;
}

QHash<int, QByteArray> XmlItem::idRoleNames()
{
    return QHash<int, QByteArray>();
}

XmlItem* XmlItem::clone()
{
    return cloneRoles(roleNames());
}

XmlItem* XmlItem::cloneAsBookmark()
{
    return cloneRoles(bookmarkRoleNames());
}

XmlItem* XmlItem::cloneRoles(QHash<int, QByteArray> roles)
{
    QHashIterator<int, QByteArray> iterator(roles);
    XmlItem* newXmlItem = create(parent());
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

bool XmlItem::isEqual(XmlItem *xmlItem)
{
    return isEqualRoles(xmlItem, idRoleNames());
}

bool XmlItem::isEqualRoles(XmlItem *xmlItem, QHash<int, QByteArray> roles)
{
    QHashIterator<int, QByteArray> iterator(roles);
    int role;
    QVariant value1, value2;

    while (iterator.hasNext()) {
        iterator.next();
        role = iterator.key();
        value1 = data(role);
        value2 = xmlItem->data(role);

        if (value1 != value2) return false;
     }

    return true;
}
