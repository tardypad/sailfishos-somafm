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
    void dataFetched();
    void networkError();
    void parsingError();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void init();

protected:
    bool m_isClonesShown;
};

#endif // XMLITEMPROXYMODEL_H
