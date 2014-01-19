#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
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
