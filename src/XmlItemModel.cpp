#include "XmlItemModel.h"

#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QXmlStreamReader>

#include "XmlItem.h"

#include "XmlItemBookmarkManager.h"

XmlItemModel::XmlItemModel(XmlItem* xmlItemPrototype, QObject *parent) :
    XmlItemAbstractListModel(xmlItemPrototype, parent),
    m_resourceUrl(""),
    m_currentReply(NULL),
    m_bookmarksManager(NULL),
    m_hasDataBeenFetchedOnce(false)
{
    m_networkManager = new QNetworkAccessManager(this);
    m_xmlReader = new QXmlStreamReader();
}

XmlItemModel::~XmlItemModel()
{
    delete m_xmlReader;
    delete m_currentReply;
    delete m_networkManager;
}

QHash<int,QByteArray> XmlItemModel::roleNames() const
{
    return m_xmlItemPrototype->roleNames();
}

void XmlItemModel::fetch()
{
    clear();
    abortFetching();
    delete m_currentReply;
    m_currentReply = NULL;

    QNetworkRequest request(m_resourceUrl);
    m_currentReply = m_networkManager->get(request);

    connect(m_currentReply, SIGNAL(finished()), this, SLOT(parse()));
    connect(m_currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(networkError()));
}

void XmlItemModel::abortFetching()
{
    if (m_currentReply != NULL && m_currentReply->isRunning()) {
        m_currentReply->disconnect(this);
        m_currentReply->abort();
    }
}

void XmlItemModel::parse()
{
    if (m_currentReply->error() != QNetworkReply::NoError)
        return;

    this->setHasDataBeenFetchedOnce(true);
    emit dataFetched();
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
}

void XmlItemModel::parseFirst()
{
}

void XmlItemModel::parseAfter()
{
}

bool XmlItemModel::stopParsing(XmlItem *xmlItem)
{
    Q_UNUSED(xmlItem);
    return false;
}

void XmlItemModel::addToBookmarks(XmlItem *xmlItem)
{
    setDataItem(xmlItem, true, XmlItem::IsBookmarkRole);
}


void XmlItemModel::removeFromBookmarks(XmlItem *xmlItem)
{
    setDataItem(xmlItem, false, XmlItem::IsBookmarkRole);
}
