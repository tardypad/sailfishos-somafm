#include "XmlItemBookmarksDatabaseManager.h"

#include <QDebug>
#include <QDir>

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
    QString dbPath(QDir::homePath());
    dbPath.append(QDir::separator()).append(_databaseName);
    db.setDatabaseName(dbPath);

    return db.open();
}

void XmlItemBookmarksDatabaseManager::init()
{
    checkStructure();
    prepareQueries();
}

