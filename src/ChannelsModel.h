#ifndef CHANNELSMODEL_H
#define CHANNELSMODEL_H

#include "XmlItemModel.h"

class Channel;

class ChannelsModel : public XmlItemModel
{
    Q_OBJECT
public:
    explicit ChannelsModel(QObject *parent = 0);
    ~ChannelsModel();

private slots:
    void addToFavorites(XmlItem* xmlItem);
    void removeFromFavorites(XmlItem* xmlItem);

private:
    virtual XmlItem* parseXmlItem();
    virtual void parseAfter();
    void duplicateGenre();
    void duplicateGenre(const QModelIndex &index);
};

#endif // CHANNELSMODEL_H
