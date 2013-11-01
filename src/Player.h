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
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE bool isPlaying(QString id);
    Q_INVOKABLE QString channelId();
    Q_INVOKABLE QString channelName();
    Q_INVOKABLE QString channelImageUrl();
    Q_INVOKABLE QString channelImageMediumUrl();

    inline Channel* channel() const { return m_channel; }
    Q_INVOKABLE inline bool isPlaying() const { return m_isPlaying; }

    inline void setChannel(Channel* channel) { m_channel = channel; emit channelChanged(); }
    inline void setIsPlaying(bool isPlaying) { m_isPlaying = isPlaying; }

protected:
    bool hasCurrentChannel();

signals:
    void channelChanged();
    void playStarted();
    void pauseStarted();

private:
    Channel* m_channel;
    bool m_isPlaying;
};

#endif // PLAYER_H
