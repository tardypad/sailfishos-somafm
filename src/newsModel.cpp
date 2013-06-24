#include "newsModel.h"

#include <QXmlStreamReader>

#include "news.h"

NewsModel::NewsModel(QObject *parent) :
    XmlModel(new News(), parent)
{
    setResourceUrl(QUrl("http://somafm.com/news.xml"));
}

XmlItem* NewsModel::parseXmlItem()
{
    News* news = new News();
    QString content = "";
    QDateTime datetime = QDateTime();

    while (!(m_xmlReader->isEndElement() && m_xmlReader->name() == m_xmlItemPrototype->xmlTag())) {
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

    news->setData(content, News::ContentRole);
    news->setData(datetime, News::DateRole);

    return news;
}
