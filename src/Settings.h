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


#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

    static const QString _qualityField;
    static const QString _formatField;
    static const QString _leftHandedField;

public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    Q_INVOKABLE QString streamQuality();
    Q_INVOKABLE QString streamFormat();
    Q_INVOKABLE bool leftHanded();
    Q_INVOKABLE void saveStreamQuality(QString quality);
    Q_INVOKABLE void saveStreamFormat(QString format);
    Q_INVOKABLE void saveLeftHanded(bool leftHanded);

protected:
    QVariant value(const QString &key);
    void setValue(const QString &key, const QVariant &value);

private:
     QSettings* m_settings;
};

#endif // SETTINGS_H
