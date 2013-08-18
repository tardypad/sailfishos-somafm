#ifndef NEWS_H
#define NEWS_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QDateTime>

#include "XmlItem.h"

class News : public XmlItem
{
    Q_OBJECT

public:
    enum Roles {
        ContentRole = XmlItem::LastRole + 1,
        DateRole,
        DateGroupRole
    };

public:
    explicit News(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();
    virtual XmlItem* create();

    virtual QString xmlTag() { return "item"; }

    inline QString content() const { return m_content; }
    inline QDateTime date() const { return m_date; }
    inline QString dateGroup() const { return m_dateGroup; }

    inline void setContent(QString content) { m_content = content; }
    inline void setDate(QDateTime date) { m_date = date; }
    inline void setDateGroup(QString dateGroup) { m_dateGroup = dateGroup; }

private:
    QString m_content;
    QDateTime m_date;
    QString m_dateGroup;
};

#endif // NEWS_H
