#ifndef CHANNELSFAVORITESDATABASEMANAGER_H
#define CHANNELSFAVORITESDATABASEMANAGER_H

#include "xmlItemBookmarksDatabaseManager.h"

class ChannelsFavoritesDatabaseManager : public XmlItemBookmarksDatabaseManager
{
    Q_OBJECT

    static const QString _channelsFavoriteTableName;

public:
    static ChannelsFavoritesDatabaseManager* instance();
    
protected:
    virtual void checkStructure();
    bool createStructure();

private:
    explicit ChannelsFavoritesDatabaseManager(QObject *parent = 0);

private:
    static ChannelsFavoritesDatabaseManager* m_instance;
};

#endif // CHANNELSFAVORITESDATABASEMANAGER_H
