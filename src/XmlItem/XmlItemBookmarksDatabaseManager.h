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


#ifndef XMLITEMBOOKMARKSDATABASEMANAGER_H
#define XMLITEMBOOKMARKSDATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class XmlItem;

class XmlItemBookmarksDatabaseManager : public QObject
{
    Q_OBJECT

    static const QString _databaseName;

public:
    ~XmlItemBookmarksDatabaseManager();
    virtual bool insertBookmark(XmlItem* xmlItem) = 0;
    virtual bool deleteBookmark(XmlItem* xmlItem) = 0;
    virtual bool removeAllBookmarks() = 0;
    virtual QList<XmlItem*> retrieveBookmarks() = 0;

protected:
    explicit XmlItemBookmarksDatabaseManager(QObject *parent = 0);
    bool openDatabase();
    QString createDatabase();
    virtual void checkStructure() = 0;
    virtual void prepareQueries() = 0;
    void init();

protected:
    static QSqlDatabase db;
    QSqlQuery insertBookmarkPreparedQuery;
    QSqlQuery deleteBookmarkPreparedQuery;
};

#endif // XMLITEMBOOKMARKSDATABASEMANAGER_H
