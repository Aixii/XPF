#ifndef TRAYICONRCLICKWGT_H
#define TRAYICONRCLICKWGT_H

#include <QWidget>

namespace Ui {
class TrayIconRClickWgt;
}

class TrayIconRClickWgt : public QWidget {
    Q_OBJECT

public:
    explicit TrayIconRClickWgt(QWidget* parent = nullptr);
    ~TrayIconRClickWgt();

    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    Ui::TrayIconRClickWgt* ui;

    // QWidget interface
protected:
    void focusOutEvent(QFocusEvent* event) override;
};

#endif // TRAYICONRCLICKWGT_H
