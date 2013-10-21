#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Channel;

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = 0);
    Q_INVOKABLE void play(Channel* channel);
    Q_INVOKABLE QString channelName();
    Q_INVOKABLE QString channelImageUrl();

    inline Channel* channel() const { return m_channel; }
    inline void setChannel(Channel* channel) { m_channel = channel; emit channelChanged(); }

signals:
    void channelChanged();

private:
    Channel* m_channel;
};

#endif // PLAYER_H
