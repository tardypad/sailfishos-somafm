#include "XmlModel.h"

#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QXmlStreamReader>

#include "XmlItem.h"

#include "XmlItemBookmarkManager.h"

XmlModel::XmlModel(XmlItem* xmlItemPrototype, QObject *parent) :
    XmlItemAbstractListModel(xmlItemPrototype, parent),
    m_resourceUrl(""),
    m_bookmarksManager(NULL),
    m_hasDataBeenFetchedOnce(false)
{
    m_networkManager = new QNetworkAccessManager(this);
    m_xmlReader = new QXmlStreamReader();
}

XmlModel::~XmlModel()
{
    delete m_xmlReader;
    delete m_networkManager;
    delete m_currentReply;
}

QHash<int,QByteArray> XmlModel::roleNames() const
{
    return m_xmlItemPrototype->roleNames();
}

void XmlModel::fetch()
{
    clear();
    QNetworkRequest request(m_resourceUrl);
    m_currentReply = m_networkManager->get(request);
    connect(m_currentReply, SIGNAL(finished()), this, SLOT(parse()));
    connect(m_currentReply, SIGNAL(finished()), this, SIGNAL(dataFetched()));
}

void XmlModel::parse()
{
    this->setHasDataBeenFetchedOnce(true);
    m_xmlReader->clear();

    QByteArray data = m_currentReply->readAll();
    m_xmlReader->addData(data);

    parseFirst();

    while (!m_xmlReader->atEnd()) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == m_xmlItemPrototype->xmlTag()) {
                XmlItem* xmlItem = parseXmlItem();

                if (stopParsing(xmlItem))
                    break;

                appendXmlItem(xmlItem);
            }
        }
    }

    parseAfter();

    m_currentReply->deleteLater();
}

void XmlModel::parseFirst()
{
}

void XmlModel::parseAfter()
{
}

bool XmlModel::stopParsing(XmlItem *xmlItem)
{
    Q_UNUSED(xmlItem);
    return false;
}

void XmlModel::addToBookmarks(XmlItem *xmlItem)
{
    setDataItem(xmlItem, true, XmlItem::IsBookmarkRole);
}


void XmlModel::removeFromBookmarks(XmlItem *xmlItem)
{
    setDataItem(xmlItem, false, XmlItem::IsBookmarkRole);
}
