#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "AbstractParser.h"

class JsonParser : public AbstractParser {
public:
    JsonParser(const QString& filePath = "", IDataExtracter* extracter = nullptr)
        : AbstractParser(filePath, extracter)
    {}
    ~JsonParser() override = default;

    bool parse() override;
};

#endif // JSONPARSER_H
