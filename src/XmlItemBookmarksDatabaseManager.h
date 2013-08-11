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

protected:
    explicit XmlItemBookmarksDatabaseManager(QObject *parent = 0);
    bool openDatabase();
    virtual void checkStructure() = 0;
    virtual void prepareQueries() = 0;
    void init();

protected:
    static QSqlDatabase db;
    QSqlQuery insertBookmarkPreparedQuery;
    QSqlQuery deleteBookmarkPreparedQuery;
};

#endif // XMLITEMBOOKMARKSDATABASEMANAGER_H
