#ifndef CHANNELSMODEL_H
#define CHANNELSMODEL_H

#include "../XmlItem/XmlItemModel.h"

class Channel;

class ChannelsModel : public XmlItemModel
{
    static const QUrl _channelsUrl;

    Q_OBJECT
public:
    explicit ChannelsModel(QObject *parent = 0);
    ~ChannelsModel();

    inline int maximumListeners() const { return m_maximumListeners; }
    inline void setMaximumListeners(int maximumListeners) { m_maximumListeners = maximumListeners; }

private slots:
    void addToFavorites(XmlItem* xmlItem);
    void removeFromFavorites(XmlItem* xmlItem);

private:
    virtual XmlItem* parseXmlItem();
    virtual void parseAfter();
    void duplicateGenre();
    void duplicateGenre(const QModelIndex &index);
    void calculMaximumListeners();

private:
    int m_maximumListeners;
};

#endif // CHANNELSMODEL_H
