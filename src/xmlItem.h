#ifndef XMLITEM_H
#define XMLITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QByteArray>
#include <QString>

class XmlItem : public QObject
{
    Q_OBJECT

public:
    enum Roles {
        IsCloneRole = Qt::UserRole + 1,
        IsBookmarkRole,
        LastRole
    };

public:
    explicit XmlItem(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual QString xmlTag() = 0;

    inline bool isClone() const { return m_isClone; }
    inline bool isBookmark() const { return m_isBookmark; }

    inline void setIsClone(bool isClone) { m_isClone = isClone; }
    inline void setIsBookmark(bool isBookmark) { m_isBookmark = isBookmark; }

protected:
    bool m_isClone;
    bool m_isBookmark;
};

#endif // XMLITEM_H
