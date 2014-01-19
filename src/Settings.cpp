#include "Settings.h"

#include <QDebug>

#include "Channel/Channel.h"

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    m_settings = new QSettings();
}

Settings::~Settings()
{
    delete m_settings;
}

QString Settings::streamQuality()
{
    if (!m_settings->contains("stream/quality")) {
        return Channel::defaultStreamQualityText();
    }

    return value("stream/quality").toString();
}

QString Settings::streamFormat()
{
    if (!m_settings->contains("stream/format")) {
        return Channel::defaultStreamFormatText();
    }

    return value("stream/format").toString();
}

bool Settings::leftHanded()
{
    if (!m_settings->contains("accessibility/lefthanded")) {
        return false;
    }

    return value("accessibility/lefthanded").toBool();
}

QVariant Settings::value(const QString &key)
{
   return m_settings->value(key);
}

void Settings::setValue(const QString &key, const QVariant &value)
{
   m_settings->setValue(key, value);
}

void Settings::saveStreamQuality(QString quality)
{
    setValue("stream/quality", quality);
}

void Settings::saveStreamFormat(QString format)
{
    setValue("stream/format", format);
}

void Settings::saveLeftHanded(bool leftHanded)
{
    setValue("accessibility/lefthanded", leftHanded);
}
