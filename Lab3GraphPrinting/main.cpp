#include "ApplicationWindow.h"

#include <QApplication>

#include <QDebug>

#include "DataExtract.h"
#include "MainController.h"
#include "DependencyInversion.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GraphDataExtracter extracter;
    DataModel dataModel;
    ApplicationWindow mainWindow;

    DIConfiguration::configure();

    MainController* controller = &MainController::instance();
    controller->setDataExtracter(&extracter);
    controller->setDataModel(&dataModel);
    controller->setView(&mainWindow);

    mainWindow.show();

    QObject::connect(&mainWindow, &ApplicationWindow::fileSelected,
                     controller, &MainController::onFileSelected);

    QObject::connect(&mainWindow, &ApplicationWindow::chartsTypeChanged,
                     controller, &MainController::onDataChanged);

    QObject::connect(&mainWindow, &ApplicationWindow::redisplayChart,
                     controller, &MainController::onDataChanged);

    QObject::connect(&dataModel, &DataModel::dataChanged,
                     controller, &MainController::onDataChanged);

    return a.exec();
}
