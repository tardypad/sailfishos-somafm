#include "Player.h"

#include <QDebug>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "Settings.h"
#include "Refresh/RefreshModel.h"
#include "Song/Song.h"

Player::Player(QObject *parent) :
    QObject(parent),
    m_channel(NULL),
    m_pls(""),
    m_hasStreamManualChoice(false),
    m_currentSong(new Song(this))
{
    m_playlist = new QMediaPlaylist(this);
    m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    m_player = new QMediaPlayer(this);
    m_player->setPlaylist(m_playlist);

    connect(this, SIGNAL(channelChanged()), this, SLOT(chosePls()));
    connect(this, SIGNAL(plsChanged()), this, SLOT(fetchPls()));

    m_refreshModel = RefreshModel::instance();
    connect(m_refreshModel, SIGNAL(refreshed()), this, SLOT(updateCurrentSong()));
    connect(this, SIGNAL(channelChanged()), this, SLOT(updateCurrentSong()));
}

Player::~Player()
{
    delete m_playlist;
}

void Player::play(Channel *channel)
{
    emit playCalled();
    connect(this, SIGNAL(playlistFilled()), this, SLOT(play()));
    setChannel(channel);
}

void Player::play()
{
    emit playCalled();
    disconnect(this, SIGNAL(playlistFilled()), this, SLOT(play()));

    if (!hasCurrentChannel()) return;

    if (!pls().isValid()) {
        connect(this, SIGNAL(playlistFilled()), this, SLOT(play()));
        chosePls();
        return;
    }

    if (m_playlist->isEmpty()) {
        connect(this, SIGNAL(playlistFilled()), this, SLOT(play()));
        fetchPls();
        return;
    }

    m_player->play();
    setIsPlaying(true);
    emit playStarted();
}

void Player::pause()
{
    m_player->pause();
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

QString Player::artist()
{
    return currentSong()->data(Song::ArtistRole).toString();
}

QString Player::title()
{
    return currentSong()->data(Song::TitleRole).toString();
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

    setHasStreamManualChoice(true);
    setStreamQualityManualChoice(quality);
    setStreamFormatManualChoice(format);
}

bool Player::hasCurrentChannel()
{
    return m_channel != NULL;
}

void Player::chosePls()
{
    Settings settings;
    QMap<Channel::StreamQuality, QMap<Channel::StreamFormat, QUrl> > allPls = channel()->getAllPlsQuality();

    Channel::StreamQuality manualQuality = streamQualityManualChoice();
    Channel::StreamQuality preferedQuality = Channel::streamQuality(settings.streamQuality());
    Channel::StreamQuality defaultQuality = Channel::defaultStreamQuality();
    Channel::StreamQuality quality;
    QMap<Channel::StreamFormat, QUrl> qualityPls;
    if (hasStreamManualChoice() && allPls.contains(manualQuality)) {
        quality = manualQuality;
    } else if (allPls.contains(preferedQuality)) {
        quality = preferedQuality;
    } else if (allPls.contains(defaultQuality)) {
        quality = defaultQuality;
    } else {
        quality = allPls.keys().first();
    }
    qualityPls = allPls.value(quality);

    Channel::StreamFormat manualFormat = streamFormatManualChoice();
    Channel::StreamFormat preferedFormat = Channel::streamFormat(settings.streamFormat());
    Channel::StreamFormat defaultFormat = Channel::defaultStreamFormat();
    Channel::StreamFormat format;
    QUrl pls;
    if (hasStreamManualChoice() && qualityPls.contains(manualFormat)) {
        format = manualFormat;
    } else if (qualityPls.contains(preferedFormat)) {
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
    m_playlist->clear();

    QNetworkRequest request(pls());
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    networkManager->get(request);

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fillPlaylist(QNetworkReply*)));
}

void Player::fillPlaylist(QNetworkReply *plsReply)
{
    if (plsReply->error() != QNetworkReply::NoError) {
        emit networkError();
        plsReply->deleteLater();
        disconnect(this, SIGNAL(playlistFilled()), this, SLOT(play()));
        return;
    }

    QString data(plsReply->readAll());
    plsReply->deleteLater();

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

void Player::updateCurrentSong()
{
    QMap<QString, QVariant> current = m_refreshModel->playing(m_channel);

    if (current.isEmpty()) return;

    QVariant artist = current.value("artist");
    QVariant title = current.value("title");

    if (artist != m_currentSong->data(Song::ArtistRole)
        || title != m_currentSong->data(Song::TitleRole)) {
        m_currentSong->setData(artist, Song::ArtistRole);
        m_currentSong->setData(title, Song::TitleRole);
        emit songChanged();
    }
}
