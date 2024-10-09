#ifndef CSTATUSLABEL_H
#define CSTATUSLABEL_H

#include <QLabel>

class CStatusLabel : public QLabel {
    Q_OBJECT
public:
    enum Status {
        Error  = 0,
        Normal = 1,
    };

    explicit CStatusLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit CStatusLabel(const QString& text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~CStatusLabel();

    void setStatus(Status);
    int  status();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Status m_status = Error;
};

#endif // CSTATUSLABEL_H
