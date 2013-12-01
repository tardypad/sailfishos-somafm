#include "Settings.h"

#include <QDebug>

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    m_settings = new QSettings();
}

Settings::~Settings()
{
    delete m_settings;
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
