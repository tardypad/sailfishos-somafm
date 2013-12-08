#include "Player.h"

#include <QDebug>

#include "Settings.h"

Player::Player(QObject *parent) :
    QObject(parent),
    m_channel(NULL),
    m_pls("")
{
    connect(this, SIGNAL(channelChanged()), this, SLOT(chosePls()));
}

void Player::play(Channel *channel)
{
    setChannel(channel);
    setIsPlaying(true);
    emit playStarted();
}

void Player::play()
{
    if (!hasCurrentChannel()) return;
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
