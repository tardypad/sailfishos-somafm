#include "xmlItemBookmarksDatabaseManager.h"

#include <QDir>

const QString XmlItemBookmarksDatabaseManager::_databaseName = "somafm.sqlite";

QSqlDatabase XmlItemBookmarksDatabaseManager::db = QSqlDatabase::addDatabase("QSQLITE");

XmlItemBookmarksDatabaseManager::XmlItemBookmarksDatabaseManager(QObject *parent) :
    QObject(parent)
{
    openDatabase();
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

