#include "Player.h"

#include <QDebug>
#include <QtMultimedia/QMediaPlaylist>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "Settings.h"

Player::Player(QObject *parent) :
    QObject(parent),
    m_channel(NULL),
    m_pls("")
{
    m_playlist = new QMediaPlaylist(this);
    m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);

    connect(this, SIGNAL(channelChanged()), this, SLOT(chosePls()));
    connect(this, SIGNAL(plsChanged()), this, SLOT(fetchPls()));
}

Player::~Player()
{
    delete m_playlist;
}

void Player::play(Channel *channel)
{
    setChannel(channel);
    connect(this, SIGNAL(playlistFilled()), this, SLOT(play()));
}

void Player::play()
{
    if (!hasCurrentChannel()) return;
    disconnect(this, SIGNAL(playlistFilled()), this, SLOT(play()));
    setIsPlaying(true);
    emit playStarted();
}

void Player::pause()
{
    if (!hasCurrentChannel()) return;
    setIsPlaying(false);
    emit pauseStarted();
}

bool Player::isPlaying(QString id)
{
    return isPlaying() && channelId() == id;
}

QString Player::channelId()
{
    if (!hasCurrentChannel()) return "";

    return channel()->data(Channel::IdRole).toString();
}

QString Player::channelName()
{
    if (!hasCurrentChannel()) return "";

    return channel()->data(Channel::NameRole).toString();
}

QString Player::channelImageUrl()
{
    if (!hasCurrentChannel()) return "";

    return channel()->data(Channel::ImageUrlRole).toString();
}

QString Player::channelImageMediumUrl()
{
    if (!hasCurrentChannel()) return "";

    return channel()->data(Channel::ImageMediumUrlRole).toString();
}

QString Player::streamQualityText()
{
    return Channel::streamQualityText(streamQuality());
}

QString Player::streamFormatText()
{
    return Channel::streamFormatText(streamFormat());
}

void Player::changeStream(QString qualityText, QString formatText)
{
    Channel::StreamQuality quality = Channel::streamQuality(qualityText);
    Channel::StreamFormat format = Channel::streamFormat(formatText);

    if (quality == streamQuality() && format == streamFormat()) return;

    QMap<Channel::StreamQuality, QMap<Channel::StreamFormat, QUrl> > allPls = channel()->getAllPlsQuality();

    if (!allPls.contains(quality) || !allPls.value(quality).contains(format)) return;

    QUrl pls = allPls.value(quality).value(format);

    setStreamQuality(quality);
    setStreamFormat(format);
    setPls(pls);
}

bool Player::hasCurrentChannel()
{
    return m_channel != NULL;
}

void Player::chosePls()
{
    Settings settings;
    QMap<Channel::StreamQuality, QMap<Channel::StreamFormat, QUrl> > allPls = channel()->getAllPlsQuality();

    Channel::StreamQuality preferedQuality = Channel::streamQuality(settings.streamQuality());
    Channel::StreamQuality defaultQuality = Channel::defaultStreamQuality();
    Channel::StreamQuality quality;
    QMap<Channel::StreamFormat, QUrl> qualityPls;
    if (allPls.contains(preferedQuality)) {
        quality = preferedQuality;
    } else if (allPls.contains(defaultQuality)) {
        quality = defaultQuality;
    } else {
        quality = allPls.keys().first();
    }
    qualityPls = allPls.value(quality);

    Channel::StreamFormat preferedFormat = Channel::streamFormat(settings.streamFormat());
    Channel::StreamFormat defaultFormat = Channel::defaultStreamFormat();
    Channel::StreamFormat format;
    QUrl pls;
    if (qualityPls.contains(preferedFormat)) {
        format = preferedFormat;
    } else if (qualityPls.contains(defaultFormat)) {
        format = defaultFormat;
    } else {
        format = qualityPls.keys().first();
    }
    pls = qualityPls.value(format);

    setStreamQuality(quality);
    setStreamFormat(format);
    setPls(pls);
}

void Player::fetchPls()
{
    QNetworkRequest request(pls());
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    networkManager->get(request);

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fillPlaylist(QNetworkReply*)));
}

void Player::fillPlaylist(QNetworkReply *plsReply)
{
    m_playlist->clear();

    QString data(plsReply->readAll());

    // QMediaPlaylist only support loading of M3U file format
    QStringList streamUrls;
    int pos = 0;
    QRegExp streamRegExp("\nFile\\d=(.*)\n");
    streamRegExp.setMinimal(true);

    while ((pos = streamRegExp.indexIn(data, pos)) != -1) {
        streamUrls << streamRegExp.cap(1);
        pos += streamRegExp.matchedLength();
    }

    for (int i = 0; i < streamUrls.size(); ++i)
        m_playlist->addMedia(QUrl(streamUrls.at(i)));

    m_playlist->setCurrentIndex(0);

    emit playlistFilled();
}
