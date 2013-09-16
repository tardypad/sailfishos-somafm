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
    Q_INVOKABLE bool addBookmark(XmlItem* xmlItem);
    Q_INVOKABLE bool removeBookmark(XmlItem* xmlItem);
    bool isBookmark(XmlItem* xmlItem) const;
    QDateTime getBookmarkDate(XmlItem* xmlItem);

protected:
    explicit XmlItemBookmarkManager(XmlItem* xmlItemPrototype, QObject *parent = 0);
    void load();

signals:
    void bookmarkAdded(XmlItem* xmlItem);
    void bookmarkRemoved(XmlItem* xmlItem);

protected:
    XmlItemBookmarksDatabaseManager* m_databaseManager;
};

#endif // XMLITEMBOOKMARKMANAGER_H
