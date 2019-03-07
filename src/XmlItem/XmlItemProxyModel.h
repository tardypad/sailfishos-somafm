/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
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
