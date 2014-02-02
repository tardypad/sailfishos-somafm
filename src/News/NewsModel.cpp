/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


#include "NewsModel.h"

#include <QDebug>
#include <QXmlStreamReader>

#include "News.h"

const QUrl NewsModel::_newsUrl = QUrl("http://somafm.com/news.xml");

NewsModel::NewsModel(QObject *parent) :
    XmlItemModel(new News(), parent),
    m_banner("")
{
    setResourceUrl(_newsUrl);
}

bool NewsModel::includeXmlItem(XmlItem *xmlItem)
{
    QDateTime date = xmlItem->data(News::DateRole).toDateTime();

    return date > QDateTime::currentDateTime().addMonths(-2);
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

    News* news = new News(this);

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
        return "This week";
    } else if (dateTime.addMonths(1) > now) {
        return "Last month";
    }

    return "Older";
}
