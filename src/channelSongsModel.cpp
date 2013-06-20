#include "channelSongsModel.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QXmlStreamReader>

#include "channelSong.h"

ChannelSongsModel::ChannelSongsModel(QObject *parent) :
    QAbstractListModel(parent), m_channelId("")
{
    m_networkManager = new QNetworkAccessManager(this);
    m_xmlReader = new QXmlStreamReader();

    setRoleNames(ChannelSong::roleNames());
}

ChannelSongsModel::~ChannelSongsModel()
{
    delete m_xmlReader;
    delete m_networkManager;
    delete m_currentReply;
    clear();
}

void ChannelSongsModel::clear()
{
    qDeleteAll(m_list);
    m_list.clear();
}

int ChannelSongsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QVariant ChannelSongsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_list.size())
        return QVariant();
    return m_list.at(index.row())->data(role);
}

bool ChannelSongsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_list.size())
        return false;
    return m_list.at(index.row())->setData(value, role);
}

void ChannelSongsModel::addChannelSong(ChannelSong *channelSong)
{
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(channelSong);
    endInsertRows();
}

void ChannelSongsModel::fetch()
{
    QNetworkRequest request(QUrl("http://somafm.com/songs/" + m_channelId + ".xml"));
    m_currentReply = m_networkManager->get(request);
    connect(m_currentReply, SIGNAL(finished()), this, SLOT(parse()));
}

void ChannelSongsModel::parse()
{
    m_list.clear();
    m_xmlReader->clear();

    QByteArray data = m_currentReply->readAll();
    m_xmlReader->addData(data);

    while (!m_xmlReader->atEnd()) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "song")
                parseChannelSong();
        }
    }

    m_currentReply->deleteLater();
}

void ChannelSongsModel::parseChannelSong()
{
    ChannelSong* channelSong = new ChannelSong();

    while (!(m_xmlReader->isEndElement() && m_xmlReader->name() == "song")) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "title") {
                m_xmlReader->readNext();
                QString title = m_xmlReader->text().toString();
                channelSong->setData(title, ChannelSong::TitleRole);
            } else if (m_xmlReader->name() == "artist") {
                m_xmlReader->readNext();
                QString artist = m_xmlReader->text().toString();
                channelSong->setData(artist, ChannelSong::ArtistRole);
            } else if (m_xmlReader->name() == "album") {
                m_xmlReader->readNext();
                QString album = m_xmlReader->text().toString();
                channelSong->setData(album, ChannelSong::AlbumRole);
            } else if (m_xmlReader->name() == "date") {
                m_xmlReader->readNext();
                int timestamp = m_xmlReader->text().toString().toInt();
                QDateTime date = QDateTime::fromTime_t(timestamp);
                channelSong->setData(date, ChannelSong::DateRole);
            }
        }
    }

    addChannelSong(channelSong);
}
