#ifndef DATAEXTRACT_H
#define DATAEXTRACT_H

#include <QDateTime>
#include <QString>
#include <QList>

class IDataExtracter {
public:
    virtual ~IDataExtracter() = default;

    virtual QDateTime extract(const QString& raw) = 0;
};



class GraphDataExtracter : public IDataExtracter {
public:
    static const QList<QString> DATA_FORMATS;
public:
    ~GraphDataExtracter() override = default;

    QDateTime extract(const QString& raw) override;
};

#endif // DATAEXTRACT_H
