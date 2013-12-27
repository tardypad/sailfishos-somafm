#ifndef NEWSMODEL_H
#define NEWSMODEL_H

#include "../XmlItem/XmlItemModel.h"

#include <QString>

class News;

class NewsModel : public XmlItemModel
{
    static const QUrl _newsUrl;
    static const QUrl _supportUrl;
    static const QUrl _twitterUrl;
    static const QUrl _facebookUrl;

    Q_OBJECT
public:
    explicit NewsModel(QObject *parent = 0);
    QUrl supportUrl();
    QUrl twitterUrl();
    QUrl facebookUrl();

    inline QString banner() { return m_banner; }
    inline void setBanner(QString banner) { m_banner = banner; }

private:
    virtual bool stopParsing(XmlItem *xmlItem);
    virtual XmlItem* parseXmlItem();
    virtual void parseFirst();
    QString defineGroup(QDateTime dateTime);

private:
    QString m_banner;
};

#endif // NEWSMODEL_H
