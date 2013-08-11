#ifndef CHANNELSFAVORITESDATABASEMANAGER_H
#define CHANNELSFAVORITESDATABASEMANAGER_H

#include "XmlItemBookmarksDatabaseManager.h"

class ChannelsFavoritesDatabaseManager : public XmlItemBookmarksDatabaseManager
{
    Q_OBJECT

    static const QString _channelsFavoriteTableName;

public:
    static ChannelsFavoritesDatabaseManager* instance();
    virtual bool insertBookmark(XmlItem *xmlItem);
    virtual bool deleteBookmark(XmlItem *xmlItem);
    virtual QList<XmlItem*> retrieveBookmarks();
    
protected:
    virtual void checkStructure();
    virtual void prepareQueries();
    bool createStructure();

private:
    explicit ChannelsFavoritesDatabaseManager(QObject *parent = 0);

private:
    static ChannelsFavoritesDatabaseManager* m_instance;
};

#endif // CHANNELSFAVORITESDATABASEMANAGER_H
