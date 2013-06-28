#ifndef SONGSBOOKMARKSMANAGER_H
#define SONGSBOOKMARKSMANAGER_H

#include <QObject>
#include <QString>

struct bookmark_t {
   QString channelId;
   QString artist;
   QString title;
};

class SongsBookmarksManager : public QObject
{
    Q_OBJECT
public:
    static SongsBookmarksManager* instance();
    Q_INVOKABLE bool addBookmark(QString channelId, QString artist, QString title);
    Q_INVOKABLE bool removeBookmark(QString channelId, QString artist, QString title);
    QList<bookmark_t> getBookmarks() const;
    bool isBookmark(QString channelId, QString artist, QString title) const;

signals:
    void bookmarkAdded(QString channelId, QString artist, QString title);
    void bookmarkRemoved(QString channelId, QString artist, QString title);

private:
    explicit SongsBookmarksManager(QObject *parent = 0);
    int indexOf(QString channelId, QString artist, QString title);

private:
    static SongsBookmarksManager* m_instance;
    QList<bookmark_t> m_bookmarks;
};

#endif // SONGSBOOKMARKSMANAGER_H
