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


#ifndef XMLITEM_H
#define XMLITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QByteArray>
#include <QString>
#include <QDateTime>

class XmlItem : public QObject
{
    Q_OBJECT

public:
    enum Roles {
        IsCloneRole = Qt::UserRole + 1,
        IsBookmarkRole,
        BookmarkDateRole,
        LastRole
    };

public:
    explicit XmlItem(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual QHash<int, QByteArray> bookmarkRoleNames();
    virtual QHash<int, QByteArray> idRoleNames();
    virtual QString xmlTag() = 0;
    virtual XmlItem* create(QObject* parent) = 0;
    virtual XmlItem* clone();
    XmlItem* cloneAsBookmark();
    bool isEqual(XmlItem* xmlItem);

    inline bool isClone() const { return m_isClone; }
    inline bool isBookmark() const { return m_isBookmark; }
    inline QDateTime bookmarkDate() const { return m_bookmarkDate; }

    inline void setIsClone(bool isClone) { m_isClone = isClone; }
    inline void setIsBookmark(bool isBookmark) { m_isBookmark = isBookmark; }
    inline void setBookmarkDate(QDateTime bookmarkDate) { m_bookmarkDate = bookmarkDate; }

private:
    XmlItem* cloneRoles(QHash<int, QByteArray> roles);
    bool isEqualRoles(XmlItem* xmlItem, QHash<int, QByteArray> roles);

protected:
    bool m_isClone;
    bool m_isBookmark;
    QDateTime m_bookmarkDate;
};

#endif // XMLITEM_H
