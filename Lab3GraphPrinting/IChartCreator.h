#ifndef ICHARTCREATOR_H
#define ICHARTCREATOR_H

#include "DataModel.h"

#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
    class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

        QT_CHARTS_USE_NAMESPACE
    class IChartCreator {
public:
    virtual ~IChartCreator() = default;

    virtual QChart* create(const QList<GraphData>& data) = 0;
};

#endif // ICHARTCREATOR_H
