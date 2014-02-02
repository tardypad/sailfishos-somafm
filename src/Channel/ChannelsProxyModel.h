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


#ifndef CHANNELSPROXYMODEL_H
#define CHANNELSPROXYMODEL_H

#include "../XmlItem/XmlItemProxyModel.h"

class XmlItem;
class Channel;
class ChannelsModel;

class ChannelsProxyModel : public XmlItemProxyModel
{
    Q_OBJECT
public:
    explicit ChannelsProxyModel(QObject *parent = 0);
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    Q_INVOKABLE void sortByListeners();
    Q_INVOKABLE void sortByGenres();
    Q_INVOKABLE void sortByName();
    Q_INVOKABLE void filterFavorites();
    Q_INVOKABLE Channel* channelItem(QString channelId);
    Q_INVOKABLE QMap<QString, QVariant> channelItemNameData(QString channelId);
    Q_INVOKABLE QList<QString> streamsQualities();
    Q_INVOKABLE QList<QString> streamsFormats();
    Q_INVOKABLE QMap<QString, QVariant> channelStreams(QString channelId);

protected:
    ChannelsModel* channelsSourceModel();
};

#endif // CHANNELSPROXYMODEL_H
