#include "channelsmodel.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "channel.h"

ChannelsModel::ChannelsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
    m_xmlReader = new QXmlStreamReader();

    setRoleNames(Channel::roleNames());
}

ChannelsModel::~ChannelsModel()
{
    delete m_xmlReader;
    delete m_networkManager;
    qDeleteAll(m_list);
    m_list.clear();
}

int ChannelsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QVariant ChannelsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_list.size())
        return QVariant();
    return m_list.at(index.row())->data(role);
}

void ChannelsModel::fetch()
{
    QNetworkRequest request(QUrl("http://somafm.com/channels.xml"));
    m_currentReply = m_networkManager->get(request);
    connect(m_currentReply, SIGNAL(readyRead()), this, SLOT(parse()));
}

void ChannelsModel::parse()
{
    m_xmlReader->clear();

    QByteArray data = m_currentReply->readAll();
    m_xmlReader->addData(data);

    while (!m_xmlReader->atEnd()) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "channel")
                parseChannel();
        }
    }
}

void ChannelsModel::parseChannel()
{
    Channel* channel = new Channel();

    QXmlStreamAttributes attributes = m_xmlReader->attributes();
    QString id = attributes.value("id").toString();
    channel->setId(id);

    while (!(m_xmlReader->isEndElement() && m_xmlReader->name() == "channel")) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "title") {
                m_xmlReader->readNext();
                QString name = m_xmlReader->text().toString();
                channel->setName(name);
            } else if (m_xmlReader->name() == "description") {
                m_xmlReader->readNext();
                QString description = m_xmlReader->text().toString();
                channel->setDescription(description);
            } else if (m_xmlReader->name() == "image") {
                m_xmlReader->readNext();
                QUrl imageUrl = QUrl(m_xmlReader->text().toString());
                channel->setImageUrl(imageUrl);
            } else if (m_xmlReader->name() == "largeimage") {
                m_xmlReader->readNext();
                QUrl imageMediumUrl = QUrl(m_xmlReader->text().toString());
                channel->setImageMediumUrl(imageMediumUrl);
            } else if (m_xmlReader->name() == "xlimage") {
                m_xmlReader->readNext();
                QUrl imageBigUrl = QUrl(m_xmlReader->text().toString());
                channel->setImageBigUrl(imageBigUrl);
            } else if (m_xmlReader->name() == "dj") {
                m_xmlReader->readNext();
                QString dj = m_xmlReader->text().toString();
                channel->setDj(dj);
            } else if (m_xmlReader->name() == "genre") {
                m_xmlReader->readNext();
                QString genre = m_xmlReader->text().toString();
                channel->setGenre(genre);
            } else if (m_xmlReader->name() == "listeners") {
                m_xmlReader->readNext();
                int listeners = m_xmlReader->text().toString().toInt();
                channel->setListeners(listeners);
            }
        }
    }

    m_list.append(channel);
}
