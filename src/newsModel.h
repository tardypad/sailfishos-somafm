#ifndef NEWSMODEL_H
#define NEWSMODEL_H

#include "xmlModel.h"

#include <QString>

class News;

class NewsModel : public XmlModel
{
    Q_OBJECT
public:
    explicit NewsModel(QObject *parent = 0);
    
    Q_INVOKABLE inline QString banner() { return m_banner; }
    inline void setBanner(QString banner) { m_banner = banner; }

private:
    virtual XmlItem* parseXmlItem();
    virtual void parseFirst();

private:
    QString m_banner;
};

#endif // NEWSMODEL_H
