#include "DataExtract.h"

const QList<QString> GraphDataExtracter::DATA_FORMATS {"dd.MM.yyyy HH:mm", "dd.MM.yyyy"};

QDateTime GraphDataExtracter::extract(const QString& raw) {
    if(raw.isEmpty()) {
        return {};
    }

    QDateTime extracted {};
    int dataFormatIndex = 0;

    extracted = QDateTime::fromString(raw, DATA_FORMATS[dataFormatIndex]);
    if(extracted.isValid()) {
        return extracted;
    }
    ++dataFormatIndex;

    auto splitRaw = raw.split(' ', Qt::SkipEmptyParts);
    if(splitRaw.size() == 2) {
        extracted = QDateTime::fromString(splitRaw[0], DATA_FORMATS[dataFormatIndex]);
        if(extracted.isValid()) {
            extracted = extracted.addSecs(splitRaw[1].toInt() * 60);
            return extracted;
        }
    }

    return {};
}
