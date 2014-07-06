/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#include "Settings.h"

#include <QDebug>

#include "Channel/Channel.h"

const QString Settings::_qualityField = QString("stream/quality");
const QString Settings::_formatField = QString("stream/format");
const QString Settings::_songCoverField = QString("display/songcover");
const QString Settings::_leftHandedField = QString("accessibility/lefthanded");

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
    if (!m_settings->contains(_qualityField)) {
        return Channel::defaultStreamQualityText();
    }

    return value(_qualityField).toString();
}

QString Settings::streamFormat()
{
    if (!m_settings->contains(_formatField)) {
        return Channel::defaultStreamFormatText();
    }

    return value(_formatField).toString();
}

bool Settings::songCover()
{
    if (!m_settings->contains(_songCoverField)) {
        return false;
    }

    return value(_songCoverField).toBool();
}

bool Settings::leftHanded()
{
    if (!m_settings->contains(_leftHandedField)) {
        return false;
    }

    return value(_leftHandedField).toBool();
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
    setValue(_qualityField, quality);
}

void Settings::saveStreamFormat(QString format)
{
    setValue(_formatField, format);
}

void Settings::saveSongCover(bool songCover)
{
    bool oldSongCover = value(_songCoverField).toBool();
    setValue(_songCoverField, songCover);
    if (oldSongCover != songCover)
        emit songCoverChanged();
}

void Settings::saveLeftHanded(bool leftHanded)
{
    setValue(_leftHandedField, leftHanded);
}
