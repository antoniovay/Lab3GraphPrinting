#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include "IChartView.h"

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTableView>
#include <QtCharts/QChartView>
#include <QtGui/qpdfwriter.h>
#include <QFileDialog>
#include <QDebug>
#include <QStatusBar>
#include <QComboBox>

class ApplicationWindow : public QMainWindow, public IChartView {
    Q_OBJECT
public:
    static const QStringList FILE_MODEL_FILTERS;

public:
    ApplicationWindow();
    ~ApplicationWindow();

    void displayChart(QtCharts::QChart* chart) override;
    void cleanChart() override;

    void showError(const QString& message) override {
        statusBar()->showMessage("Ошибка: " + message, 5000);
        qDebug() << "Ошибка:" << message;
    }

    void showStatus(const QString& message) override {
        statusBar()->showMessage(message, 3000);
        qDebug() << "Статус:" << message;
    }

signals:
    void fileSelected(const QString& filePath);
    void chartsTypeChanged();
    void redisplayChart();

private slots:
    void _showFileDialog();
    void _selectionChanged(const QItemSelection &selected);
    void _chartTypeChanged(int index);
    void _bwToggled(bool checked) {
        if(!_chartView && !_chart) {
            return;
        }
        if(!checked) {
            emit redisplayChart();
            return;
        }

        _chartView->chart()->setTheme(QtCharts::QChart::ChartThemeHighContrast);
        if (auto *xAxis = _chartView->chart()->axes(Qt::Horizontal).value(0)) {
            xAxis->setShadesVisible(false);
        }
        if (auto *yAxis = _chartView->chart()->axes(Qt::Vertical).value(0)) {
            yAxis->setShadesVisible(false);
        }
    }
    void _printButtonClicked() {
        if(_chart->series().isEmpty()) {
            showError("Нельзя напечатать пустой график. . .");
            return;
        }

        QString filePath = QFileDialog::getSaveFileName(this, "Сохранить график", "", "PDF (*.pdf)");
        if (!filePath.isEmpty())
        {
            QPdfWriter pdfWriter(filePath);
            QPainter painter(&pdfWriter);
            _chartView->render(&painter);
        }
    }

private:
    void _setCenterAnchor();
    void _setDefaultViewConfiguration();


private:
    QFileSystemModel *_model = nullptr;
    QTableView *_tableView = nullptr;
    QtCharts::QChartView *_chartView = nullptr;
    QtCharts::QChart* _chart = nullptr;

    QComboBox* _comboBox = nullptr;
};

#endif // APPLICATIONWINDOW_H
