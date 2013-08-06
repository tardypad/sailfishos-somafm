#include "xmlModel.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QXmlStreamReader>

#include "xmlItem.h"
#include "xmlItemBookmarkManager.h"

XmlModel::XmlModel(XmlItem* xmlItemPrototype, QObject *parent) :
    QAbstractListModel(parent),
    m_resourceUrl(""),
    m_xmlItemPrototype(xmlItemPrototype),
    m_bookmarksManager(NULL)

{
    m_networkManager = new QNetworkAccessManager(this);
    m_xmlReader = new QXmlStreamReader();
}

XmlModel::~XmlModel()
{
    delete m_xmlReader;
    delete m_networkManager;
    delete m_currentReply;
    delete m_xmlItemPrototype;
    clear();
}

void XmlModel::clear()
{
    beginResetModel();
    qDeleteAll(m_list);
    m_list.clear();
    endResetModel();
}

int XmlModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QHash<int,QByteArray> XmlModel::roleNames() const
{
    return m_xmlItemPrototype->roleNames();
}

QVariant XmlModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_list.size())
        return QVariant();
    return m_list.at(index.row())->data(role);
}

bool XmlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_list.size())
        return false;

    bool result = m_list.at(index.row())->setData(value, role);

    if (result)
        emit dataChanged(index, index);

    return result;
}

void XmlModel::setDataItem(XmlItem *xmlItem, const QVariant &value, int role)
{
    for (int row = 0; row < m_list.size(); ++row) {
        if (m_list.at(row)->isEqual(xmlItem)) {
            setData(index(row) ,value, role);
        }
    }
}

XmlItem* XmlModel::itemAt(int row)
{
    if (row < 0 || row >= m_list.size())
        return NULL;

    return m_list.at(row);
}

void XmlModel::appendXmlItem(XmlItem *xmlItem)
{
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(xmlItem);
    endInsertRows();
}

void XmlModel::fetch()
{
    QNetworkRequest request(m_resourceUrl);
    m_currentReply = m_networkManager->get(request);
    connect(m_currentReply, SIGNAL(finished()), this, SLOT(parse()));
}

void XmlModel::parse()
{
    clear();
    m_xmlReader->clear();

    QByteArray data = m_currentReply->readAll();
    m_xmlReader->addData(data);

    parseFirst();

    while (!m_xmlReader->atEnd()) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement()) {
            if (m_xmlReader->name() == m_xmlItemPrototype->xmlTag()) {
                XmlItem* xmlItem = parseXmlItem();
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

void XmlModel::addToBookmarks(XmlItem *xmlItem)
{
    setDataItem(xmlItem, true, XmlItem::IsBookmarkRole);
}


void XmlModel::removeFromBookmarks(XmlItem *xmlItem)
{
    setDataItem(xmlItem, false, XmlItem::IsBookmarkRole);
}
