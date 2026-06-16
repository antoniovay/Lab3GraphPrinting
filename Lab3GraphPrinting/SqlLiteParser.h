#ifndef SQLLITEPARSER_H
#define SQLLITEPARSER_H

#include "AbstractParser.h"

class SqlLiteParser : public AbstractParser {
public:
    SqlLiteParser(const QString& filePath = "", IDataExtracter* extracter = nullptr)
        : AbstractParser(filePath, extracter)
    {}
    ~SqlLiteParser() override = default;

    bool parse() override;
};

#endif // SQLLITEPARSER_H
