#ifndef SUPPORTMODEL_H
#define SUPPORTMODEL_H

#include <QUrl>

#include "../XmlItem/XmlItemModel.h"

class SupportModel : public XmlItemModel
{
    static const QUrl _supportUrl;

    Q_OBJECT
public:
    explicit SupportModel(QObject *parent = 0);

    Q_INVOKABLE inline QString banner() { return m_banner; }
    inline void setBanner(QString banner) { m_banner = banner; }

private:
    virtual XmlItem* parseXmlItem();
    virtual void parseFirst();

private:
    QString m_banner;
};

#endif // SUPPORTMODEL_H
