/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
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
    QString dbDirPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
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

