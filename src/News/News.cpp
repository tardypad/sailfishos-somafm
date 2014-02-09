/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#include "News.h"

#include <QDebug>

News::News(QObject *parent) :
    XmlItem(parent),
    m_content(""),
    m_date(QDateTime()),
    m_dateGroup("")
{
}

QHash<int, QByteArray> News::roleNames()
{
    QHash<int, QByteArray> roleNames = XmlItem::roleNames();

    roleNames[ContentRole] = "content";
    roleNames[DateRole] = "date";
    roleNames[DateGroupRole] = "dateGroup";

    return roleNames;
}

QVariant News::data(int role) const
{
    switch(role) {
    case ContentRole:
        return content();
    case DateRole:
        return date();
    case DateGroupRole:
        return dateGroup();
    }

    return XmlItem::data(role);
}

bool News::setData(const QVariant &value, int role)
{
    switch(role) {
    case ContentRole:
        setContent(value.toString());
        return true;
    case DateRole:
        setDate(value.toDateTime());
        return true;
    case DateGroupRole:
        setDateGroup(value.toString());
        return true;
    }

    return XmlItem::setData(value, role);
}

XmlItem* News::create(QObject *parent)
{
    return new News(parent);
}
