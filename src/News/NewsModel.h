#ifndef NEWSMODEL_H
#define NEWSMODEL_H

#include "../XmlItem/XmlItemModel.h"

#include <QString>

class News;

class NewsModel : public XmlItemModel
{
    static const QUrl _newsUrl;

    Q_OBJECT
public:
    explicit NewsModel(QObject *parent = 0);
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
