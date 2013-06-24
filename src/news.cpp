#include "news.h"

News::News(QObject *parent) :
    XmlItem(parent),
    m_content(""),
    m_date(QDateTime())
{
}

QHash<int, QByteArray> News::roleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[ContentRole] = "content";
    roleNames[DateRole] = "date";

    return roleNames;
}

QVariant News::data(int role) const
{
    switch(role) {
    case ContentRole:
        return content();
    case DateRole:
        return date();
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
    }

    return false;
}
