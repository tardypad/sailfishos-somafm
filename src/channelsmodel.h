#ifndef CHANNELSMODEL_H
#define CHANNELSMODEL_H

#include <QAbstractListModel>

class Channel;
class QXmlStreamReader;
class QNetworkAccessManager;
class QNetworkReply;

class ChannelsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ChannelsModel(QObject *parent = 0);
    ~ChannelsModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void fetch();

private slots:
    void parse();

private:
    void parseChannel();
    void duplicateGenre(Channel* channel);

private:
    QList<Channel*> m_list;
    QXmlStreamReader* m_xmlReader;
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_currentReply;
};

#endif // CHANNELSMODEL_H
