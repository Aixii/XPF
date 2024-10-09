#ifndef IR_PARAMVALUESSETWGT_H
#define IR_PARAMVALUESSETWGT_H

#include <QWidget>

namespace Ui {
class IR_ParamValuesSetWgt;
}

class IR_ParamValuesSetWgt : public QWidget {
    Q_OBJECT

public:
    explicit IR_ParamValuesSetWgt(QWidget* parent = nullptr);
    ~IR_ParamValuesSetWgt();

    void setTitle(const QString& title);

    QStringList getValues();

    void setValues(QStringList list);

private slots:
    void on_toolButton_Add_clicked();

    void on_toolButton_Edit_clicked();

    void on_toolButton_Delete_clicked();

private:
    Ui::IR_ParamValuesSetWgt* ui;
};

#endif // IR_PARAMVALUESSETWGT_H
