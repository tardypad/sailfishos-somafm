#include "news.h"

News::News(QObject *parent) :
    XmlItem(parent),
    m_content(""),
    m_date(QDateTime()),
    m_dateGroup("")
{
}

QHash<int, QByteArray> News::roleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[ContentRole] = "content";
    roleNames[DateRole] = "date";
    roleNames[DateGroupRole] = "dateGroup";

    return roleNames;
}

QVariant News::data(int role) const
{
    switch(role) {
    case ContentRole:
        return content();
    case DateRole:
        return date();
    case DateGroupRole:
        return dateGroup();
    }

    return QVariant();
}

bool News::setData(const QVariant &value, int role)
{
    switch(role) {
    case ContentRole:
        setContent(value.toString());
        return true;
    case DateRole:
        setDate(value.toDateTime());
        return true;
    case DateGroupRole:
        setDateGroup(value.toString());
        return true;
    }

    return false;
}
