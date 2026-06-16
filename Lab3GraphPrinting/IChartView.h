#ifndef ICHARTVIEW_H
#define ICHARTVIEW_H

#include <QtCharts/QChart>

class IChartView {
public:
    virtual ~IChartView() = default;

    virtual void displayChart(QtCharts::QChart* chart) = 0;
    virtual void cleanChart() = 0;
    virtual void showError(const QString& message) = 0;
    virtual void showStatus(const QString& message) = 0;
};

#endif // ICHARTVIEW_H
