#ifndef SCATTERCHARTCREATOR_H
#define SCATTERCHARTCREATOR_H

#include "AbstractChartCreator.h"

#include <QtCharts/QScatterSeries>

class ScatterChartCreator : public AbstractChartCreator {
protected:
    QAbstractSeries* createSeries(const QList<GraphData>& data) override {
        QScatterSeries* series = new QScatterSeries();
        for (const auto& point : data) {
            series->append(point.xAxis, point.yAxis);
        }

        series->setMarkerSize(5.0);

        return series;
    }

    QString getChartTitle() const override {
        return "Scatter chart";
    }
};

#endif // SCATTERCHARTCREATOR_H
