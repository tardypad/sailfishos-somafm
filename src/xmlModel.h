#ifndef XMLMODEL_H
#define XMLMODEL_H

#include <QAbstractListModel>
#include <QUrl>

class QXmlStreamReader;
class QNetworkAccessManager;
class QNetworkReply;

class XmlItemBookmarkManager;
class XmlItem;

class XmlModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit XmlModel(XmlItem* xmlItemPrototype, QObject *parent = 0);
    ~XmlModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QHash<int,QByteArray> roleNames() const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Q_INVOKABLE void fetch();
    Q_INVOKABLE XmlItem* itemAt(int row);

protected slots:
    void addToBookmarks(XmlItem* xmlItem);
    void removeFromBookmarks(XmlItem* xmlItem);

protected:
    inline void setResourceUrl(QUrl resourceUrl) { m_resourceUrl = resourceUrl; }
    void appendXmlItem(XmlItem* xmlItem);
    void clear();
    void setDataItem(XmlItem* xmlItem, const QVariant &value, int role);

private slots:
    virtual void parseFirst();
    void parse();
    virtual void parseAfter();

private:
    virtual XmlItem* parseXmlItem() = 0;

protected:
    QUrl m_resourceUrl;
    XmlItem* m_xmlItemPrototype;
    QList<XmlItem*> m_list;
    QXmlStreamReader* m_xmlReader;
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_currentReply;
    XmlItemBookmarkManager* m_bookmarksManager;
};

#endif // XMLMODEL_H
