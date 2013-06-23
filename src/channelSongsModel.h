#ifndef CHANNELSONGSMODEL_H
#define CHANNELSONGSMODEL_H

#include "xmlModel.h"

class ChannelSong;
class BookmarksManager;

class ChannelSongsModel : public XmlModel
{
    Q_OBJECT
public:
    explicit ChannelSongsModel(QObject *parent = 0);
    ~ChannelSongsModel();
    Q_INVOKABLE void setChannelId(QString channelId);
    void setDataSong(QString artist, QString title, const QVariant &value, int role);

private slots:
    void addToBookmarks(QString artist, QString title);
    void removeFromBookmarks(QString artist, QString title);

private:
    virtual XmlItem* parseXmlItem();

private:
    BookmarksManager* m_bookmarksManager;
};

#endif // CHANNELSONGSMODEL_H
