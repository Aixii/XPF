#include "IR_ParamValuesSetWgt.h"
#include "ui_IR_ParamValuesSetWgt.h"

IR_ParamValuesSetWgt::IR_ParamValuesSetWgt(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::IR_ParamValuesSetWgt) {
    ui->setupUi(this);
}

IR_ParamValuesSetWgt::~IR_ParamValuesSetWgt() {
    delete ui;
}

void IR_ParamValuesSetWgt::setTitle(const QString& title) {
    ui->label_title->setText(title);
}

QStringList IR_ParamValuesSetWgt::getValues() {
    QStringList list;

    int rowCount = ui->listWidget->count();
    for (int index = 0; index < rowCount; index++) {
        QString text = ui->listWidget->item(index)->text();
        if (text.isEmpty()) {
            continue;
        }
        list.append(text);
    }
    return list;
}

void IR_ParamValuesSetWgt::setValues(QStringList list) {
    ui->listWidget->clear();
    ui->listWidget->addItems(list);
}

void IR_ParamValuesSetWgt::on_toolButton_Add_clicked() {
    int rowCount = ui->listWidget->count();

    QListWidgetItem* item;

    if (rowCount > 0 && ui->listWidget->item(rowCount - 1)->text().isEmpty()) {
        item = ui->listWidget->item(rowCount - 1);
    }
    else {
        item = new QListWidgetItem(ui->listWidget);
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setText("");
        ui->listWidget->addItem(item);
    }

    item->setSelected(true);
    ui->listWidget->editItem(item);
}

void IR_ParamValuesSetWgt::on_toolButton_Edit_clicked() {
    QListWidgetItem* item = ui->listWidget->currentItem();
    ui->listWidget->editItem(item);
}

void IR_ParamValuesSetWgt::on_toolButton_Delete_clicked() {
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    for (QListWidgetItem* item : items) {
        ui->listWidget->removeItemWidget(item);
        delete item;
    }
}
