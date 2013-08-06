#ifndef XMLITEMBOOKMARKMANAGER_H
#define XMLITEMBOOKMARKMANAGER_H

#include <QAbstractListModel>

class XmlItem;

class XmlItemBookmarkManager : public QAbstractListModel
{
    Q_OBJECT
public:
    ~XmlItemBookmarkManager();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QHash<int,QByteArray> roleNames() const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE bool addBookmark(XmlItem* xmlItem);
    Q_INVOKABLE bool removeBookmark(XmlItem* xmlItem);
    bool isBookmark(XmlItem* xmlItem) const;

protected:
    explicit XmlItemBookmarkManager(XmlItem* xmlItemPrototype, QObject *parent = 0);
    void clear();
    QModelIndex indexOf(XmlItem* xmlItem) const;

signals:
    void bookmarkAdded(XmlItem* xmlItem);
    void bookmarkRemoved(XmlItem* xmlItem);

protected:
    XmlItem* m_xmlItemPrototype;
    QList<XmlItem*> m_bookmarksList;
};

#endif // XMLITEMBOOKMARKMANAGER_H
