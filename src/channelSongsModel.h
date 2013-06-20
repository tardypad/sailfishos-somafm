#ifndef CHANNELSONGSMODEL_H
#define CHANNELSONGSMODEL_H

#include <QAbstractListModel>

class ChannelSong;
class QXmlStreamReader;
class QNetworkAccessManager;
class QNetworkReply;

class ChannelSongsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ChannelSongsModel(QObject *parent = 0);
    ~ChannelSongsModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Q_INVOKABLE void fetch();

    inline QString channelId() { return m_channelId; }
    Q_INVOKABLE inline void setChannelId(QString channelId) { m_channelId = channelId; }

private slots:
    void parse();

private:
    void parseChannelSong();
    void addChannelSong(ChannelSong* channelSong);
    void clear();
        
private:
    QString m_channelId;
    QList<ChannelSong*> m_list;
    QXmlStreamReader* m_xmlReader;
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_currentReply;
};

#endif // CHANNELSONGSMODEL_H
