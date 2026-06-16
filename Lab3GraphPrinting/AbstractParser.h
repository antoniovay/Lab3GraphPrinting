#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include "IParser.h"
#include "DataExtract.h"

#include <QVector>
#include <QDateTime>

class AbstractParser : public IParser {
public:
    AbstractParser(const QString& filePath = "", IDataExtracter* extracter = nullptr)
        : _filePath(filePath), _dataExtracter(extracter)
    {}
    ~AbstractParser() override = default;

    QString getFilePath() const override {return _filePath;}
    void setFilePath(const QString& filePath) override {_filePath = filePath;}

    IDataExtracter* getDataExtracter() const {return _dataExtracter;}
    void setDataExtracter(IDataExtracter* extracter) {_dataExtracter = extracter;}

    QList<GraphData> getData() override {
        QList<GraphData> result;
        getData(result);
        return result;
    }
    void getData(QList<GraphData>& out) override {std::swap(out, _data);}

protected:
    QList<GraphData> _data {};

private:
    QString _filePath {""};
    IDataExtracter* _dataExtracter {nullptr};
};

#endif // ABSTRACTPARSER_H
