#ifndef CREFRESHBUTTON_H
#define CREFRESHBUTTON_H

#include <QPushButton>
#include <QTimer>

class CRefreshButton : public QPushButton {
    Q_OBJECT
public:
    explicit CRefreshButton(QWidget* parent = nullptr);
    ~CRefreshButton();

    void init();

    void start();
    void stop();
    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void slotRotate();

private:
    int     m_Angle;
    QTimer* m_Timer;
    QPixmap m_pixmap;
};

#endif // CREFRESHBUTTON_H
