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
