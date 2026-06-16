#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "DependencyInversion.h"

#include "DataModel.h"
#include "IChartView.h"

#include <QObject>
#include <QFileInfo>

class MainController : public QObject {
    Q_OBJECT
public:
    static const QStringList FILE_TYPES;
public:
    MainController(const MainController& other) = delete;

    static MainController& instance() {
        static MainController controller;
        return controller;
    }

    void setView(IChartView* view) {_view = view;}
    void setDataModel(IDataModel* model) {_model = model;}
    void setDataExtracter(IDataExtracter* extracter) {_extracter = extracter;}

    MainController& operator = (const MainController& other) = delete;

public slots:
    void onFileSelected(const QString& filePath) {
        if(!_view) {
            throw std::runtime_error("Отсутствует главное окно");
        }
        if(!_model) {
            throw std::runtime_error("Отсутствует модель данных!");
        }

        _view->showStatus("Загрузка файла. . . " + filePath);

        QFileInfo fileInfo(filePath);
        QString extension = fileInfo.suffix().toLower();
        if(extension == FILE_TYPES[0]) {
            DIConfiguration::switchToJsonParser(_extracter);
        } else if (extension == FILE_TYPES[1]){
            DIConfiguration::switchToSqlLiteParser(_extracter);
        }

        auto parser = gContainer.GetObject<IParser>();
        if(!parser) {
            _view->showError("Не подключен обработчик данных. . .");
            return;
        }

        parser->setFilePath(filePath);
        if(!parser->parse()) {
            _model->setData({});
            _view->showError("Не удалось обработать файл: " + filePath);
            _view->cleanChart();
            return;
        }

        _model->setData(parser->getData());
        if (_model->getData().empty()) {
            _view->showError("Не найдены данные в файле.");
            return;
        }

        _view->showStatus("Данные успешно обработаны! " + filePath);

        _view->showStatus(QString("Загружено %1 точек из файла %2")
                              .arg(_model->getData().size())
                              .arg(filePath));
    }

    void onDataChanged() {
        if(!_view) {
            throw std::runtime_error("Отсутствует главное окно");
        }
        if(!_model) {
            throw std::runtime_error("Отсутствует модель данных!");
        }

        auto chartCreator = gContainer.GetObject<IChartCreator>();
        if (!chartCreator) {
            throw std::runtime_error("Отсутствует генератор графиков");
        }
        if (_model->getData().empty()) {
            _view->showError("Нельзя напечатать график, если данных нет. . .");
            return;
        }

        _view->showStatus("Идет генерация графика. . .");

        auto chart = chartCreator->create(_model->getData());
        if(!chart) {
            _view->showError("Ошибка генерации графика. . .");
            return;
        }

        _view->showStatus("Генерация графика прошла успешно!");

        _view->displayChart(chart);
    }
private:
    MainController() = default;

private:
    IChartView* _view = nullptr;
    IDataModel* _model = nullptr;
    IDataExtracter* _extracter = nullptr;
};

#endif // MAINCONTROLLER_H
