#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>

struct GraphData {
    qint64 xAxis {};
    double yAxis {};
};

class IDataModel {
public:
    virtual QList<GraphData> getData() const = 0;
    virtual void setData(QList<GraphData>&& data) = 0;
};

class DataModel : public QObject, public IDataModel {
    Q_OBJECT
public:
    QList<GraphData> getData() const override {return _data;}
    void setData(QList<GraphData>&& data) override {
        _data = data;
        emit dataChanged();
    }

signals:
    void dataChanged();

private:
    QList<GraphData> _data;
};

#endif // DATAMODEL_H
