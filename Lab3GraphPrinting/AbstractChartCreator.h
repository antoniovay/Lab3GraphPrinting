#ifndef ABSTRACTCHARTCREATOR_H
#define ABSTRACTCHARTCREATOR_H

#include "IChartCreator.h"

#include <QtCharts/QChart>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QDateTime>

#include <QDebug>

QT_CHARTS_USE_NAMESPACE

    class AbstractChartCreator : public IChartCreator {
public:
    virtual ~AbstractChartCreator() override = default;

    QChart* create(const QList<GraphData>& data) override {
        QChart* chart = new QChart();
        chart->setTitle(getChartTitle());

        QAbstractSeries* series = createSeries(data);
        if (!series) {
            throw std::runtime_error("Cant create series");
            return chart;
        }

        setSeriesConfiguration(series);

        chart->addSeries(series);

        setupAxes(chart, series, data);

        return chart;
    }

protected:
    virtual QAbstractSeries* createSeries(const QList<GraphData>& data) = 0;

    virtual QString getChartTitle() const = 0;

    virtual void setSeriesConfiguration(QAbstractSeries* series) {}

    virtual void setupAxes(QChart* chart, QAbstractSeries* series, const QList<GraphData>& data) {
        QDateTimeAxis* axisX = new QDateTimeAxis();
        axisX->setFormat("dd.MM.yyyy HH:mm");
        axisX->setTitleText("Дата");
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->legend()->hide();
        series->attachAxis(axisX);

        QValueAxis* axisY = new QValueAxis();
        axisY->setTitleText("Значение");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        if (!data.isEmpty()) {
            axisX->setMin(QDateTime::fromMSecsSinceEpoch(data.first().xAxis));
            axisX->setMax(QDateTime::fromMSecsSinceEpoch(data.last().xAxis));
            double minY = std::min_element(data.begin(), data.end(),
                                           [](const GraphData& a, const GraphData& b) {return a.yAxis < b.yAxis;})->yAxis;
            double maxY = std::max_element(data.begin(), data.end(),
                                           [](const GraphData& a, const GraphData& b) {return a.yAxis < b.yAxis;})->yAxis;
            axisY->setMin(minY - 1.0);
            axisY->setMax(maxY + 1.0);
        }
    }
};

#endif // ABSTRACTCHARTCREATOR_H
