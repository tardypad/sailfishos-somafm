#ifndef BOOKMARKSMANAGER_H
#define BOOKMARKSMANAGER_H

#include <QObject>
#include <QString>

struct bookmark_t {
   QString artist;
   QString title;
};

class BookmarksManager : public QObject
{
    Q_OBJECT
public:
    static BookmarksManager* instance();
    Q_INVOKABLE bool addBookmark(QString artist, QString title);
    Q_INVOKABLE bool removeBookmark(QString artist, QString title);
    QList<bookmark_t> getBookmarks() const;
    bool isBookmark(QString artist, QString title) const;

signals:
    void bookmarkAdded(QString artist, QString title);
    void bookmarkRemoved(QString artist, QString title);

private:
    explicit BookmarksManager(QObject *parent = 0);
    int indexOf(QString artist, QString title);

private:
    static BookmarksManager* m_instance;
    QList<bookmark_t> m_bookmarks;
};

#endif // BOOKMARKSMANAGER_H
