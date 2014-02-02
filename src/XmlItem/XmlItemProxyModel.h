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


#ifndef XMLITEMPROXYMODEL_H
#define XMLITEMPROXYMODEL_H

#include "XmlItemAbstractSortFilterProxyModel.h"

class XmlItem;
class XmlItemModel;

class XmlItemProxyModel : public XmlItemAbstractSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit XmlItemProxyModel(QObject *parent = 0);
    virtual bool filterAcceptsRow (int source_row, const QModelIndex& source_parent) const;
    Q_INVOKABLE void fetch();
    Q_INVOKABLE void abortFetching();
    Q_INVOKABLE bool hasDataBeenFetchedOnce();
    Q_INVOKABLE void sortByBookmarkDate();
    Q_INVOKABLE void showClones(bool show = true);
    Q_INVOKABLE void hideClones();
    Q_INVOKABLE void filterBookmarks();

    inline bool isClonesShown() const { return m_isClonesShown; }
    inline void setIsClonesShown(bool isClonesShown) { m_isClonesShown = isClonesShown; }

protected:
    XmlItemModel* xmlItemSourceModel();

signals:
    void fetchStarted();
    void dataFetched();
    void dataParsed();
    void networkError();
    void parsingError();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

protected slots:
    virtual void init();

protected:
    bool m_isClonesShown;
};

#endif // XMLITEMPROXYMODEL_H
