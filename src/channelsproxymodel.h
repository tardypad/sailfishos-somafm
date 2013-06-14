#ifndef CHANNELSPROXYMODEL_H
#define CHANNELSPROXYMODEL_H

#include <QSortFilterProxyModel>

class ChannelsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ChannelsProxyModel(QObject *parent = 0);
    virtual bool filterAcceptsRow (int source_row, const QModelIndex& source_parent) const;
    Q_INVOKABLE void sortByListeners();
    Q_INVOKABLE void sortByGenres();
    Q_INVOKABLE void filterFavorites();
    Q_INVOKABLE void showClones(bool show = true);
    Q_INVOKABLE void hideClones();
    Q_INVOKABLE void clearFilter();

    inline bool isClonesShown() const { return m_isClonesShown; }
    inline void setIsClonesShown(bool isClonesShown) { m_isClonesShown = isClonesShown; }

private:
    bool m_isClonesShown;
};

#endif // CHANNELSPROXYMODEL_H
