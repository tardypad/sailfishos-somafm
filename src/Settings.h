/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
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
    static const QString _songCoverField;
    static const QString _leftHandedField;

public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    Q_INVOKABLE QString streamQuality();
    Q_INVOKABLE QString streamFormat();
    Q_INVOKABLE bool songCover();
    Q_INVOKABLE bool leftHanded();
    Q_INVOKABLE void saveStreamQuality(QString quality);
    Q_INVOKABLE void saveStreamFormat(QString format);
    Q_INVOKABLE void saveSongCover(bool songCover);
    Q_INVOKABLE void saveLeftHanded(bool leftHanded);

protected:
    QVariant value(const QString &key);
    void setValue(const QString &key, const QVariant &value);

signals:
    void songCoverChanged();

private:
     QSettings* m_settings;
};

#endif // SETTINGS_H
