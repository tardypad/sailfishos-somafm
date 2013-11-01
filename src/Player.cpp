#include "Player.h"

#include <QDebug>

#include "Channel/Channel.h"

Player::Player(QObject *parent) :
    QObject(parent),
    m_channel(NULL)
{
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

bool Player::hasCurrentChannel()
{
    return m_channel != NULL;
}
