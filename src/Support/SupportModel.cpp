#include "SupportModel.h"

#include <QDebug>
#include <QXmlStreamReader>

#include "Support.h"

const QUrl SupportModel::_supportUrl = QUrl("http://somafm.com/support.xml");

SupportModel::SupportModel(QObject *parent) :
    XmlItemModel(new Support(), parent),
    m_banner("")
{
    setResourceUrl(_supportUrl);
}

void SupportModel::parseFirst()
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

XmlItem* SupportModel::parseXmlItem()
{
    Support* support = new Support();
    QString content = "";
    QString location = "";

    while (!m_xmlReader->atEnd() &&
           !(m_xmlReader->isEndElement() && m_xmlReader->name() == m_xmlItemPrototype->xmlTag())) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == "content") {
                m_xmlReader->readNext();
                content = m_xmlReader->text().toString();
            } else if (m_xmlReader->name() == "location") {
                m_xmlReader->readNext();
                location = m_xmlReader->text().toString();
            }
        }
    }

    if (m_xmlReader->hasError())
        return NULL;

    support->setData(content, Support::ContentRole);
    support->setData(location, Support::LocationRole);

    return support;
}
