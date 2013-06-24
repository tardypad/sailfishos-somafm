#ifndef NEWSMODEL_H
#define NEWSMODEL_H

#include "xmlModel.h"

class News;

class NewsModel : public XmlModel
{
    Q_OBJECT
public:
    explicit NewsModel(QObject *parent = 0);
    
private:
    virtual XmlItem* parseXmlItem();
};

#endif // NEWSMODEL_H
