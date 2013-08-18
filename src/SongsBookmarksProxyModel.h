#ifndef SONGSBOOKMARKSPROXYMODEL_H
#define SONGSBOOKMARKSPROXYMODEL_H

#include <QSortFilterProxyModel>

class XmlItem;

class SongsBookmarksProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SongsBookmarksProxyModel(QObject *parent = 0);
    Q_INVOKABLE XmlItem* itemAt(int row);
    Q_INVOKABLE void sortByDate();
    Q_INVOKABLE void sortByChannel();
    Q_INVOKABLE bool addBookmark(XmlItem* xmlItem);
    Q_INVOKABLE bool removeBookmark(XmlItem* xmlItem);
    Q_INVOKABLE bool isEmpty() const;
};

#endif // SONGSBOOKMARKSPROXYMODEL_H
