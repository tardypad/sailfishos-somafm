#include "Player.h"

#include <QDebug>

#include "Channel/Channel.h"
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

    QString imageMediumUrl = channel()->data(Channel::ImageMediumUrlRole).toString();

    if (imageMediumUrl.isEmpty())
        return channel()->data(Channel::ImageBigUrlRole).toString();

    return imageMediumUrl;
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
    QMap<Channel::StreamFormat, QUrl> qualityPls;
    if (allPls.contains(preferedQuality)) {
        qualityPls = allPls.value(preferedQuality);
    } else {
        qualityPls = allPls.values().first();
    }

    Channel::StreamFormat preferedFormat = Channel::streamFormat(settings.streamFormat());
    QUrl pls;
    if (qualityPls.contains(preferedFormat)) {
        pls = qualityPls.value(preferedFormat);
    } else {
        pls = qualityPls.values().first();
    }

    setPls(pls);
}
