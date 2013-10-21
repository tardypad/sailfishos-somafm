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
}

QString Player::channelName()
{
    if (m_channel == NULL) return "";

    return channel()->data(Channel::NameRole).toString();
}

QString Player::channelImageUrl()
{
    if (m_channel == NULL) return "";

    return channel()->data(Channel::ImageUrlRole).toString();
}
