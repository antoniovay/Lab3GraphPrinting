#ifndef AREACHARTCREATOR_H
#define AREACHARTCREATOR_H

#include "AbstractChartCreator.h"

#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>

class AreaChartCreator : public AbstractChartCreator {
protected:
    QAbstractSeries* createSeries(const QList<GraphData>& data) override {
        QLineSeries* upperSeries = new QLineSeries();
        for (const auto& point : data) {
            upperSeries->append(point.xAxis, point.yAxis);
        }

        QLineSeries* lowerSeries = new QLineSeries();
        for (const auto& point : data) {
            lowerSeries->append(point.xAxis, 0);
        }

        QAreaSeries* series = new QAreaSeries(upperSeries, lowerSeries);
        return series;
    }

    QString getChartTitle() const override {
        return "Area chart";
    }
};

#endif // AREACHARTCREATOR_H
