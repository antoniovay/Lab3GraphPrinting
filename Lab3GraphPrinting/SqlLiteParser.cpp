#include "SqlLiteParser.h"

#include <QtSql>
#include <QDebug>

bool SqlLiteParser::parse() {
    if(!getDataExtracter()) {
        throw std::runtime_error("JsonParser: _dataExtracter cant be nullptr");
        return false;
    }

    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");

    dataBase.setDatabaseName(getFilePath());
    if(!dataBase.open()) {
        return false;
    }

    auto tables = dataBase.tables();
    if(tables.isEmpty()) {
        dataBase.close();
        return false;
    }

    QList<GraphData> parsed;

    QSqlQuery query;
    if(!query.exec("SELECT * FROM " + tables.first())) {
        dataBase.close();
        return false;
    } else {
        while(query.next()) {
            QString rawData = query.value(0).toString();
            QDateTime data = getDataExtracter()->extract(rawData);
            if(!data.isValid()) {
                return false;
            }
            qint64 parsetDataTime = data.toMSecsSinceEpoch();

            bool ok;
            double value = query.value(1).toDouble(&ok);
            if(!ok) {
                return false;
            }

            parsed.push_back({parsetDataTime,
                              value});
        }
    }
    dataBase.close();

    std::swap(_data, parsed);

    return true;
}
