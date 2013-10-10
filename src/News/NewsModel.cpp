#include "NewsModel.h"

#include <QDebug>
#include <QXmlStreamReader>

#include "../SomaFM.h"
#include "News.h"

NewsModel::NewsModel(QObject *parent) :
    XmlItemModel(new News(), parent),
    m_banner("")
{
    setResourceUrl(SomaFM::newsUrl());
}

QUrl NewsModel::supportUrl()
{
    return SomaFM::supportUrl();
}

bool NewsModel::stopParsing(XmlItem *xmlItem)
{
    QDateTime date = xmlItem->data(News::DateRole).toDateTime();

    return date.addMonths(2) < QDateTime::currentDateTime();
}

void NewsModel::parseFirst()
{
    QString banner = "";

    while (!m_xmlReader->atEnd() &&
           !(m_xmlReader->isEndElement() && m_xmlReader->name() == "banner")) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement() && m_xmlReader->name() == "banner") {
            m_xmlReader->readNext();
            banner = m_xmlReader->text().toString();
        }
    }

    if (!m_xmlReader->hasError())
        setBanner(banner);
}

XmlItem* NewsModel::parseXmlItem()
{
    News* news = new News();
    QString content = "";
    QDateTime datetime = QDateTime();
    QString dateGroup = "";

    while (!m_xmlReader->atEnd() &&
           !(m_xmlReader->isEndElement() && m_xmlReader->name() == m_xmlItemPrototype->xmlTag())) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "content") {
                m_xmlReader->readNext();
                content = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "date") {
                m_xmlReader->readNext();
                int timestamp = m_xmlReader->text().toString().toInt();
                datetime = QDateTime::fromTime_t(timestamp);
            }
        }
    }

    if (m_xmlReader->hasError())
        return NULL;

    dateGroup = defineGroup(datetime);

    news->setData(content, News::ContentRole);
    news->setData(datetime, News::DateRole);
    news->setData(dateGroup, News::DateGroupRole);

    return news;
}

QString NewsModel::defineGroup(QDateTime dateTime)
{
    if (!dateTime.isValid()) return "";

    QDateTime now = QDateTime::currentDateTime();

    if (dateTime.addDays(7) > now) {
        return "Last week";
    } else if (dateTime.addMonths(1) > now) {
        return "Last month";
    }

    return "Older";
}
