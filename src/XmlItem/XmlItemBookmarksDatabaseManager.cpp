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

