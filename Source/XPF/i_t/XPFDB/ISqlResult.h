#pragma once

#include <QStringList>
#include <QVariant>

class ISqlResult  {

public:
    ISqlResult() { }
    virtual ~ISqlResult() { }

    virtual int fieldsCount() = 0;

    virtual QStringList fieldes() = 0;
    virtual QString     fieldName(int index) = 0;
    virtual int         fieldIndexOf(const QString& name) = 0;

    virtual int rowCount() = 0;

    virtual QVariantList row(int rowIndex) = 0;
    virtual QVariant     rowData(int rowIndex, int colunmIndex) = 0;

    virtual bool isError() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isValid() = 0;

    virtual int errorType() = 0;
    virtual QString errorText() = 0;
};
