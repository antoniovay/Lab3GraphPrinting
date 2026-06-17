#ifndef DEPENDENCYINVERSION_H
#define DEPENDENCYINVERSION_H

#include "ioc_contaner.h"

#include "IParser.h"
#include "JsonParser.h"
#include "SqlLiteParser.h"

#include "IChartCreator.h"
#include "LineChartCreator.h"
#include "AreaChartCreator.h"
#include "SplineChartCreator.h"
#include "ScatterChartCreator.h"

#include "DataExtract.h"

#include <QObject>
#include <QtCore/qdebug.h>

extern IOCContainer gContainer;

class DIConfiguration {
public:
    static void configure() {
        gContainer.RegisterInstance<IParser, JsonParser>();

        gContainer.RegisterInstance<IChartCreator, LineChartCreator>();
    }

    static void switchToJsonParser(IDataExtracter* extracter) {
        gContainer.RegisterInstance<IParser>(std::make_shared<JsonParser>("", extracter));
    }
    static void switchToSqlLiteParser(IDataExtracter* extracter) {
        gContainer.RegisterInstance<IParser>(std::make_shared<SqlLiteParser>("", extracter));
    }

    static void switchToLineChart() {
        gContainer.RegisterInstance<IChartCreator, LineChartCreator>();
        qDebug() << "Switched to LineChartCreator";
    }
    static void switchToAreaChart() {
        gContainer.RegisterInstance<IChartCreator, AreaChartCreator>();
        qDebug() << "Switched to AreaChartCreator";
    }
    static void switchToSplineChart() {
        gContainer.RegisterInstance<IChartCreator, SplineChartCreator>();
        qDebug() << "Switched to SplineChartCreator";
    }
    static void switchToScatterChart() {
        gContainer.RegisterInstance<IChartCreator, ScatterChartCreator>();
        qDebug() << "Switched to ScatterChartCreator";
    }

};

#endif // DEPENDENCYINVERSION_H
