#ifndef LINECHARTCREATOR_H
#define LINECHARTCREATOR_H

#include "AbstractChartCreator.h"

#include <QtCharts/QLineSeries>

class LineChartCreator : public AbstractChartCreator {
protected:
    QAbstractSeries* createSeries(const QList<GraphData>& data) override {
        QLineSeries* series = new QLineSeries();
        for (const auto& point : data) {
            series->append(point.xAxis, point.yAxis);
        }
        return series;
    }

    QString getChartTitle() const override {
        return "Line chart";
    }
};

#endif // LINECHARTCREATOR_H
