#ifndef XMLITEM_H
#define XMLITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QByteArray>
#include <QString>
#include <QDateTime>

class XmlItem : public QObject
{
    Q_OBJECT

public:
    enum Roles {
        IsCloneRole = Qt::UserRole + 1,
        IsBookmarkRole,
        BookmarkDateRole,
        LastRole
    };

public:
    explicit XmlItem(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual QHash<int, QByteArray> bookmarkRoleNames();
    virtual QHash<int, QByteArray> idRoleNames();
    virtual QString xmlTag() = 0;
    virtual XmlItem* create() = 0;
    XmlItem* clone();
    XmlItem* cloneAsBookmark();
    bool isEqual(XmlItem* xmlItem);

    inline bool isClone() const { return m_isClone; }
    inline bool isBookmark() const { return m_isBookmark; }
    inline QDateTime bookmarkDate() const { return m_bookmarkDate; }

    inline void setIsClone(bool isClone) { m_isClone = isClone; }
    inline void setIsBookmark(bool isBookmark) { m_isBookmark = isBookmark; }
    inline void setBookmarkDate(QDateTime bookmarkDate) { m_bookmarkDate = bookmarkDate; }

private:
    XmlItem* cloneRoles(QHash<int, QByteArray> roles);
    bool isEqualRoles(XmlItem* xmlItem, QHash<int, QByteArray> roles);

protected:
    bool m_isClone;
    bool m_isBookmark;
    QDateTime m_bookmarkDate;
};

#endif // XMLITEM_H
