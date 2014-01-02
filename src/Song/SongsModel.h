#ifndef SONGSMODEL_H
#define SONGSMODEL_H

#include "../XmlItem/XmlItemModel.h"

class Song;
class Channel;

class SongsModel : public XmlItemModel
{
    static const QUrl _channelSongsUrl;

    Q_OBJECT
public:
    explicit SongsModel(QObject *parent = 0);
    ~SongsModel();
    void setChannel(XmlItem* channel);
    void fetchAdditional();

signals:
    void fetchUpdateStarted();
    void fetchUpdateFinished();

private slots:
    void parseAdditional();

private:
    virtual bool includeXmlItem(XmlItem *xmlItem);
    virtual XmlItem* parseXmlItem();

private:
    Channel* m_channel;
};

#endif // SONGSMODEL_H
