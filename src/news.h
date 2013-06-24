#ifndef NEWS_H
#define NEWS_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <QDateTime>

#include "xmlItem.h"

class News : public XmlItem
{
    Q_OBJECT

public:
    enum Roles {
        ContentRole = Qt::UserRole+1,
        DateRole
    };

public:
    explicit News(QObject *parent = 0);
    virtual QVariant data(int role) const;
    virtual bool setData (const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames();

    virtual QString xmlTag() { return "item"; }

    inline QString content() const { return m_content; }
    inline QDateTime date() const { return m_date; }

    inline void setContent(QString content) { m_content = content; }
    inline void setDate(QDateTime date) { m_date = date; }

private:
    QString m_content;
    QDateTime m_date;
};

#endif // NEWS_H
