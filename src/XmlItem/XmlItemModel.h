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
    void removeAllFromBookmarks();

protected:
    inline void setResourceUrl(QUrl resourceUrl) { m_resourceUrl = resourceUrl; }
    inline QUrl resourceUrl() const { return m_resourceUrl; }
    void launchDownload();
    void setHasDataBeenFetchedOnce(bool hasDataBeenFetchedOnce) { m_hasDataBeenFetchedOnce = hasDataBeenFetchedOnce; }
    void setClearBeforeFetching(bool clearBeforeFetching) { m_clearBeforeFetching = clearBeforeFetching; }

private slots:
    virtual void parseFirst();
    void parse();
    virtual void parseAfter();

private:
    virtual bool includeXmlItem(XmlItem* xmlItem);
    virtual XmlItem* parseXmlItem() = 0;

protected:
    QUrl m_resourceUrl;
    QXmlStreamReader* m_xmlReader;
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_currentReply;
    XmlItemBookmarkManager* m_bookmarksManager;
    bool m_hasDataBeenFetchedOnce;
    bool m_clearBeforeFetching;
};

#endif // XMLITEMMODEL_H
