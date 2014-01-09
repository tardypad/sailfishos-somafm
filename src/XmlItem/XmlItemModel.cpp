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
    m_hasDataBeenFetchedOnce(false),
    m_clearBeforeFetching(true)
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

void XmlItemModel::launchDownload()
{
    abortFetching();
    delete m_currentReply;
    m_currentReply = NULL;

    QNetworkRequest request(resourceUrl());
    m_currentReply = m_networkManager->get(request);
}

void XmlItemModel::fetch()
{
    if (m_clearBeforeFetching) clear();
    launchDownload();
    emit fetchStarted();

    connect(m_currentReply, SIGNAL(finished()), this, SLOT(parse()));
    connect(m_currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(networkError()));
    connect(m_currentReply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
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

    emit dataFetched();
    m_xmlReader->clear();

    QByteArray data = m_currentReply->readAll();
    m_xmlReader->addData(data);

    QList<XmlItem*> tmp_list;

    parseFirst();

    while (!m_xmlReader->atEnd()) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == m_xmlItemPrototype->xmlTag()) {
                XmlItem* xmlItem = parseXmlItem();

                if (!xmlItem) {
                    emit parsingError();
                    return;
                }

                if (!includeXmlItem(xmlItem)) {
                    delete xmlItem;
                    continue;
                }

                tmp_list.append(xmlItem);
            }
        }
    }

    if (m_xmlReader->hasError()) {
        emit parsingError();
        return;
    }

    appendXmlItems(tmp_list);
    emit dataParsed();

    this->setHasDataBeenFetchedOnce(true);

    parseAfter();
}

void XmlItemModel::parseFirst()
{
}

void XmlItemModel::parseAfter()
{
}

bool XmlItemModel::includeXmlItem(XmlItem *xmlItem)
{
    Q_UNUSED(xmlItem);
    return true;
}

void XmlItemModel::addToBookmarks(XmlItem *xmlItem)
{
    setDataItem(xmlItem, true, XmlItem::IsBookmarkRole);
}

void XmlItemModel::removeFromBookmarks(XmlItem *xmlItem)
{
    setDataItem(xmlItem, false, XmlItem::IsBookmarkRole);
}

void XmlItemModel::removeAllFromBookmarks()
{
    setDataAll(false, XmlItem::IsBookmarkRole);
}
