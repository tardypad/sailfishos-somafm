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


#include "XmlItemBookmarksDatabaseManager.h"

#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

const QString XmlItemBookmarksDatabaseManager::_databaseName = "somafm.sqlite";

QSqlDatabase XmlItemBookmarksDatabaseManager::db = QSqlDatabase::addDatabase("QSQLITE");

XmlItemBookmarksDatabaseManager::XmlItemBookmarksDatabaseManager(QObject *parent) :
    QObject(parent)
{
    if (!db.isOpen()) {
        openDatabase();

        // "Relink" queries to the opened database
        insertBookmarkPreparedQuery.clear();
        deleteBookmarkPreparedQuery.clear();
    }
}

XmlItemBookmarksDatabaseManager::~XmlItemBookmarksDatabaseManager()
{
    QSqlDatabase::removeDatabase(_databaseName);
}

bool XmlItemBookmarksDatabaseManager::openDatabase()
{
    QString dbPath = QStandardPaths::locate(QStandardPaths::DataLocation, _databaseName);

    if (dbPath.isEmpty()) {
        dbPath = createDatabase();
    }

    db.setDatabaseName(dbPath);

    return db.open();
}

QString XmlItemBookmarksDatabaseManager::createDatabase()
{
    QString dbDirPath = QStandardPaths::standardLocations(QStandardPaths::DataLocation).first();
    QDir dbDir;
    dbDir.mkpath(dbDirPath);
    QString dbPath = dbDirPath.append(QDir::separator()).append(_databaseName);
    QFile dbFile(dbPath);
    dbFile.open(QIODevice::WriteOnly);
    return dbPath;
}

void XmlItemBookmarksDatabaseManager::init()
{
    checkStructure();
    prepareQueries();
}

