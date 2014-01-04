#ifndef SUPPORT_H
#define SUPPORT_H

#include <QUrl>

#include "../XmlItem/XmlItem.h"

class Support : public XmlItem
{
    Q_OBJECT

public:
    enum Roles {
        ContentRole = XmlItem::LastRole + 1,
        LocationRole
    };

public:
    explicit Support(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual XmlItem* create(QObject *parent);

    virtual QString xmlTag() { return "item"; }

    inline QString content() const { return m_content; }
    inline QUrl location() const { return m_location; }

    inline void setContent(QString content) { m_content = content; }
    inline void setLocation(QUrl location) { m_location = location; }

private:
    QString m_content;
    QUrl m_location;
};

#endif // SUPPORT_H
