#include "somaFM.h"

const QString SomaFM::_channelsUrl = "http://somafm.com/channels.xml";
const QString SomaFM::_channelSongsUrl = "http://somafm.com/songs/:channelId:.xml";
const QString SomaFM::_newsUrl = "http://somafm.com/news.xml";
const QString SomaFM::_supportUrl = "http://somafm.com/support";

SomaFM::SomaFM(QObject *parent) :
    QObject(parent)
{
}

QUrl SomaFM::channelsUrl()
{
    return QUrl(_channelsUrl);
}

QUrl SomaFM::channelSongsUrl(QString channelId)
{
    QString url = _channelSongsUrl;
    url.replace(":channelId:", channelId);

    return QUrl(url);
}

QUrl SomaFM::newsUrl()
{
    return QUrl(_newsUrl);
}

QUrl SomaFM::supportUrl()
{
    return QUrl(_supportUrl);
}
