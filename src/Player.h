#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QUrl>
#include "Channel/Channel.h"

class QMediaPlaylist;
class QMediaPlayer;
class QNetworkReply;
class RefreshModel;
class Song;

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = 0);
    ~Player();
    Q_INVOKABLE void play(Channel* channel);
    Q_INVOKABLE void pause();
    Q_INVOKABLE bool isPlaying(QString id);
    Q_INVOKABLE QString channelId();
    Q_INVOKABLE QString channelName();
    Q_INVOKABLE QString channelImageUrl();
    Q_INVOKABLE QString channelImageMediumUrl();
    Q_INVOKABLE QString artist();
    Q_INVOKABLE QString title();
    Q_INVOKABLE QString streamQualityText();
    Q_INVOKABLE QString streamFormatText();
    Q_INVOKABLE void changeStream(QString qualityText, QString formatText);

    Q_INVOKABLE inline Channel* channel() const { return m_channel; }
    Q_INVOKABLE inline bool isPlaying() const { return m_isPlaying; }
    Q_INVOKABLE inline Song* currentSong() const { return m_currentSong; }
    inline QUrl pls() const { return m_pls; }
    inline bool hasStreamManualChoice() const { return m_hasStreamManualChoice; }
    inline Channel::StreamQuality streamQualityManualChoice() const { return m_streamQualityManualChoice; }
    inline Channel::StreamFormat streamFormatManualChoice() const { return m_streamFormatManualChoice; }
    inline Channel::StreamQuality streamQuality() const { return m_streamQuality; }
    inline Channel::StreamFormat streamFormat() const { return m_streamFormat; }
    inline QMediaPlaylist* playlist() const { return m_playlist; }

    inline void setChannel(Channel* channel) { m_channel = channel; emit channelChanged(); }
    inline void setIsPlaying(bool isPlaying) { m_isPlaying = isPlaying; }
    inline void setPls(QUrl pls) { m_pls = pls; emit plsChanged(); }
    inline void setHasStreamManualChoice(bool hasStreamManualChoice) { m_hasStreamManualChoice = hasStreamManualChoice; }
    inline void setStreamQualityManualChoice(Channel::StreamQuality streamQualityManualChoice) { m_streamQualityManualChoice = streamQualityManualChoice; }
    inline void setStreamFormatManualChoice(Channel::StreamFormat streamFormatManualChoice) { m_streamFormatManualChoice = streamFormatManualChoice; }
    inline void setStreamQuality(Channel::StreamQuality streamQuality) { m_streamQuality = streamQuality; }
    inline void setStreamFormat(Channel::StreamFormat streamFormat) { m_streamFormat = streamFormat; }

public slots:
    Q_INVOKABLE void play();

protected:
    bool hasCurrentChannel();

protected slots:
    void chosePls();
    void fetchPls();
    void fillPlaylist(QNetworkReply* plsReply);
    void updateCurrentSong();

signals:
    void channelChanged();
    void plsChanged();
    void playlistFilled();
    void networkError();
    void playCalled();
    void playStarted();
    void pauseStarted();
    void songChanged();

private:
    Channel* m_channel;
    bool m_isPlaying;
    QUrl m_pls;
    bool m_hasStreamManualChoice;
    Channel::StreamQuality m_streamQualityManualChoice;
    Channel::StreamFormat m_streamFormatManualChoice;
    Channel::StreamQuality m_streamQuality;
    Channel::StreamFormat m_streamFormat;
    QMediaPlaylist* m_playlist;
    QMediaPlayer* m_player;
    RefreshModel* m_refreshModel;
    Song* m_currentSong;
};

#endif // PLAYER_H
