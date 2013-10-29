#include "Player.h"

#include "Channel/Channel.h"

Player::Player(QObject *parent) :
    QObject(parent),
    m_channel(NULL)
{
}

void Player::play(Channel *channel)
{
    setChannel(channel);
    emit playStarted();
}

void Player::play()
{
    if (!hasCurrentChannel()) return;

    emit playStarted();
}

void Player::pause()
{
    if (!hasCurrentChannel()) return;

    emit pauseStarted();
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

bool Player::hasCurrentChannel()
{
    return m_channel != NULL;
}
