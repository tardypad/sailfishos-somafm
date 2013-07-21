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
