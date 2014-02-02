/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


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
