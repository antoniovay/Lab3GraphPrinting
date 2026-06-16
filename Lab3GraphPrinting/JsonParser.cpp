#include "JsonParser.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

bool JsonParser::parse() {
    if(!getDataExtracter()) {
        throw std::runtime_error("JsonParser: _dataExtracter cant be nullptr");
        return false;
    }

    QFile file(getFilePath());

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        return false;
    }

    if (!jsonDoc.isArray()) {
        return false;
    }

    QList<GraphData> parsed;

    QJsonArray rootArray = jsonDoc.array();
    for (auto it = rootArray.begin(); it != rootArray.end(); ++it) {
        if (!it->isArray()) {
            return false;
        }

        QJsonArray innerArray = it->toArray();
        if (innerArray.size() != 2) {
            return false;
        }

        QDateTime data = getDataExtracter()->extract(innerArray[0].toString());
        if(!data.isValid()) {
            return false;
        }
        qint64 parsetDataTime = data.toMSecsSinceEpoch();

        if(!innerArray[1].isDouble()) {
            return false;
        }
        double value = innerArray[1].toDouble();

        parsed.push_back({parsetDataTime,
                          value});
    }

    std::swap(_data, parsed);

    return true;
}