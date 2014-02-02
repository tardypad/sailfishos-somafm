/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


#include "Settings.h"

#include <QDebug>

#include "Channel/Channel.h"

const QString Settings::_qualityField = QString("stream/quality");
const QString Settings::_formatField = QString("stream/format");
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

void Settings::saveLeftHanded(bool leftHanded)
{
    setValue(_leftHandedField, leftHanded);
}
