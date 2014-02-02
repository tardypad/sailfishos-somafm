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


#include "SongsProxyModel.h"

#include "SongsModel.h"
#include "Song.h"

SongsProxyModel::SongsProxyModel(QObject *parent) :
    XmlItemProxyModel(parent)
{
}

SongsModel *SongsProxyModel::songsSourceModel()
{
    return (SongsModel*) sourceModel();
}

void SongsProxyModel::init()
{
    XmlItemProxyModel::init();
    connect(songsSourceModel(), SIGNAL(fetchUpdateStarted()), this, SIGNAL(fetchUpdateStarted()));
    connect(songsSourceModel(), SIGNAL(fetchUpdateFinished()), this, SIGNAL(fetchUpdateFinished()));
}

void SongsProxyModel::setChannel(XmlItem *channel)
{
    return songsSourceModel()->setChannel(channel);
}

void SongsProxyModel::fetchAdditional()
{
    return songsSourceModel()->fetchAdditional();
}

void SongsProxyModel::sortByDate()
{
    setSortRole(Song::DateRole);
    sort(0, Qt::DescendingOrder);
}
