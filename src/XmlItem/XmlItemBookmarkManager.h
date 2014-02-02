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


#ifndef XMLITEMBOOKMARKMANAGER_H
#define XMLITEMBOOKMARKMANAGER_H

#include "XmlItemAbstractListModel.h"

class XmlItemBookmarksDatabaseManager;

class XmlItemBookmarkManager : public XmlItemAbstractListModel
{
    Q_OBJECT
public:
    ~XmlItemBookmarkManager();
    virtual QHash<int,QByteArray> roleNames() const;
    bool addBookmark(XmlItem* xmlItem);
    bool removeBookmark(XmlItem* xmlItem);
    bool removeAllBookmarks();
    bool isBookmark(XmlItem* xmlItem) const;
    QDateTime getBookmarkDate(XmlItem* xmlItem);

protected:
    explicit XmlItemBookmarkManager(XmlItem* xmlItemPrototype, QObject *parent = 0);
    void load();

signals:
    void bookmarkAdded(XmlItem* xmlItem);
    void bookmarkRemoved(XmlItem* xmlItem);
    void allBookmarksRemoved();

protected:
    XmlItemBookmarksDatabaseManager* m_databaseManager;
};

#endif // XMLITEMBOOKMARKMANAGER_H
