#ifndef SONGSMODEL_H
#define SONGSMODEL_H

#include "xmlModel.h"

class Song;
class SongsBookmarksManager;

class SongsModel : public XmlModel
{
    Q_OBJECT
public:
    explicit SongsModel(QObject *parent = 0);
    ~SongsModel();
    Q_INVOKABLE void setChannelId(QString channelId);
    void setDataSong(QString artist, QString title, const QVariant &value, int role);

private slots:
    void addToBookmarks(QString channelId, QString artist, QString title);
    void removeFromBookmarks(QString channelId, QString artist, QString title);

private:
    virtual XmlItem* parseXmlItem();

private:
    QString m_channelId;
    SongsBookmarksManager* m_bookmarksManager;
};

#endif // SONGSMODEL_H
