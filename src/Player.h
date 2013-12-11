#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QUrl>
#include "Channel/Channel.h"

class QMediaPlaylist;
class QNetworkReply;

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = 0);
    ~Player();
    Q_INVOKABLE void play(Channel* channel);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE bool isPlaying(QString id);
    Q_INVOKABLE QString channelId();
    Q_INVOKABLE QString channelName();
    Q_INVOKABLE QString channelImageUrl();
    Q_INVOKABLE QString channelImageMediumUrl();
    Q_INVOKABLE QString streamQualityText();
    Q_INVOKABLE QString streamFormatText();
    Q_INVOKABLE void changeStream(QString qualityText, QString formatText);

    Q_INVOKABLE inline Channel* channel() const { return m_channel; }
    Q_INVOKABLE inline bool isPlaying() const { return m_isPlaying; }
    inline QUrl pls() const { return m_pls; }
    inline Channel::StreamQuality streamQuality() const { return m_streamQuality; }
    inline Channel::StreamFormat streamFormat() const { return m_streamFormat; }
    inline QMediaPlaylist* playlist() const { return m_playlist; }

    inline void setChannel(Channel* channel) { m_channel = channel; emit channelChanged(); }
    inline void setIsPlaying(bool isPlaying) { m_isPlaying = isPlaying; }
    inline void setPls(QUrl pls) { m_pls = pls; emit plsChanged(); }
    inline void setStreamQuality(Channel::StreamQuality streamQuality) { m_streamQuality = streamQuality; }
    inline void setStreamFormat(Channel::StreamFormat streamFormat) { m_streamFormat = streamFormat; }

protected:
    bool hasCurrentChannel();

protected slots:
    void chosePls();
    void fetchPls();
    void fillPlaylist(QNetworkReply* plsReply);

signals:
    void channelChanged();
    void plsChanged();
    void playStarted();
    void pauseStarted();

private:
    Channel* m_channel;
    bool m_isPlaying;
    QUrl m_pls;
    Channel::StreamQuality m_streamQuality;
    Channel::StreamFormat m_streamFormat;
    QMediaPlaylist* m_playlist;
};

#endif // PLAYER_H
