#ifndef XMLITEMBOOKMARKSDATABASEMANAGER_H
#define XMLITEMBOOKMARKSDATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class XmlItemBookmarksDatabaseManager : public QObject
{
    Q_OBJECT

    static const QString _databaseName;

public:
    ~XmlItemBookmarksDatabaseManager();

protected:
    explicit XmlItemBookmarksDatabaseManager(QObject *parent = 0);
    bool openDatabase();
    virtual void checkStructure() = 0;

protected:
    static QSqlDatabase db;
};

#endif // XMLITEMBOOKMARKSDATABASEMANAGER_H
