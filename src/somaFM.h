#ifndef SOMAFM_H
#define SOMAFM_H

#include <QObject>
#include <QUrl>
#include <QString>

class SomaFM : public QObject
{
    static const QString _channelsUrl;
    static const QString _channelSongsUrl;
    static const QString _newsUrl;

    Q_OBJECT
public:
    explicit SomaFM(QObject *parent = 0);
    static QUrl channelsUrl();
    static QUrl channelSongsUrl(QString channelId);
    static QUrl newsUrl();
};

#endif // SOMAFM_H
