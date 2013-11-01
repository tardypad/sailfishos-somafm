#ifndef XMLITEMMODEL_H
#define XMLITEMMODEL_H

#include <QUrl>

#include "XmlItemAbstractListModel.h"

class QXmlStreamReader;
class QNetworkAccessManager;
class QNetworkReply;

class XmlItemBookmarkManager;

class XmlItemModel : public XmlItemAbstractListModel
{
    Q_OBJECT
public:
    explicit XmlItemModel(XmlItem* xmlItemPrototype, QObject *parent = 0);
    ~XmlItemModel();
    virtual QHash<int,QByteArray> roleNames() const;
    Q_INVOKABLE void fetch();
    Q_INVOKABLE void abortFetching();
    Q_INVOKABLE bool hasDataBeenFetchedOnce() { return m_hasDataBeenFetchedOnce; }

signals:
    void fetchStarted();
    void dataFetched();
    void dataParsed();
    void networkError();
    void parsingError();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

protected slots:
    void addToBookmarks(XmlItem* xmlItem);
    void removeFromBookmarks(XmlItem* xmlItem);

protected:
    inline void setResourceUrl(QUrl resourceUrl) { m_resourceUrl = resourceUrl; }
    inline QUrl resourceUrl() const { return m_resourceUrl; }

private slots:
    virtual void parseFirst();
    void parse();
    virtual void parseAfter();

private:
    virtual bool stopParsing(XmlItem* xmlItem);
    virtual XmlItem* parseXmlItem() = 0;
    void setHasDataBeenFetchedOnce(bool hasDataBeenFetchedOnce) { m_hasDataBeenFetchedOnce = hasDataBeenFetchedOnce; }

protected:
    QUrl m_resourceUrl;
    QXmlStreamReader* m_xmlReader;
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_currentReply;
    XmlItemBookmarkManager* m_bookmarksManager;
    bool m_hasDataBeenFetchedOnce;
};

#endif // XMLITEMMODEL_H
