#ifndef IPARSER_H
#define IPARSER_H

#include "DataModel.h"

#include <QString>

class IParser {
public:
    virtual ~IParser() = default;

    virtual QString getFilePath() const = 0;
    virtual void setFilePath(const QString& filePath) = 0;

    virtual bool parse() = 0;

    virtual QList<GraphData> getData() = 0;
    virtual void getData(QList<GraphData>& out) = 0;
};

#endif // IPARSER_H
