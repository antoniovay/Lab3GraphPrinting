#ifndef SPLINECHARTCREATOR_H
#define SPLINECHARTCREATOR_H

#include "AbstractChartCreator.h"

#include <QtCharts/QSplineSeries>

class SplineChartCreator : public AbstractChartCreator {
protected:
    QAbstractSeries* createSeries(const QList<GraphData>& data) override {
        QSplineSeries* series = new QSplineSeries();
        for (const auto& point : data) {
            series->append(point.xAxis, point.yAxis);
        }
        return series;
    }

    QString getChartTitle() const override {
        return "Spline chart";
    }
};

#endif // SPLINECHARTCREATOR_H
