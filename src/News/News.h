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


#ifndef NEWS_H
#define NEWS_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QDateTime>

#include "../XmlItem/XmlItem.h"

class News : public XmlItem
{
    Q_OBJECT

public:
    enum Roles {
        ContentRole = XmlItem::LastRole + 1,
        DateRole,
        DateGroupRole
    };

public:
    explicit News(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual XmlItem* create(QObject *parent);

    virtual QString xmlTag() { return "item"; }

    inline QString content() const { return m_content; }
    inline QDateTime date() const { return m_date; }
    inline QString dateGroup() const { return m_dateGroup; }

    inline void setContent(QString content) { m_content = content; }
    inline void setDate(QDateTime date) { m_date = date; }
    inline void setDateGroup(QString dateGroup) { m_dateGroup = dateGroup; }

private:
    QString m_content;
    QDateTime m_date;
    QString m_dateGroup;
};

#endif // NEWS_H
