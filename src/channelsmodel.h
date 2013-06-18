#ifndef CHANNELSMODEL_H
#define CHANNELSMODEL_H

#include <QAbstractListModel>

class Channel;
class QXmlStreamReader;
class QNetworkAccessManager;
class QNetworkReply;
class FavoritesManager;

class ChannelsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ChannelsModel(QObject *parent = 0);
    ~ChannelsModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void setDataChannel(QString channelId, const QVariant &value, int role);
    void setFavoritesManager(FavoritesManager* favoritesManager);
    void fetch();

private slots:
    void parse();
    void addToFavorites(QString channelId);
    void removeFromFavorites(QString channelId);

private:
    void parseChannel();
    void duplicateGenre(Channel* channel);

private:
    QList<Channel*> m_list;
    QXmlStreamReader* m_xmlReader;
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_currentReply;
    FavoritesManager* m_favoritesManager;
};

#endif // CHANNELSMODEL_H
