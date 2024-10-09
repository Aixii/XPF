#ifndef IR_INSTRUMENTPANEL_H
#define IR_INSTRUMENTPANEL_H

#include <QPainter>
#include <QTimer>
#include <QWidget>

/*
    仪表盘
*/

#define PANEL_COVER_DEG 150.0 // 仪表盘所占角度（范围0.0~360.0）
#define PANEL_COVER_DEG_HALF (PANEL_COVER_DEG * 0.5)
#define PANEL_ROTATE_DEG (90.0 - PANEL_COVER_DEG_HALF) // 起始旋转角度
#define PANEL_MARGIN_PIX 5 // 外边距

class IR_InstrumentPanel : public QWidget {
    Q_OBJECT

public:
    IR_InstrumentPanel(QWidget* parent = nullptr);

    ~IR_InstrumentPanel();

    // 设置刻度范围和刻度数(刻度数量至少为2)
    void setScaleRange(const double& minVal, const double& maxVal, const int seg = 5);

    // 设置当前刻度值
    void setScaleValue(const double& val);

    // 设置门限值（true-低于该值警告 false-高于）
    void setThreshold(const double& val, bool isLower = true);

    void setUnit(const QString& unit);

private:
    // 绘图原点h方向平移值
    int m_moveH;

    // 仪表盘弧所处圆半径
    int m_panelRadiuPix;

    // 刻度间隔(角度)
    double m_scaleInv;

    // 空白区域像素
    int m_blankPix;

    // 刻度文本间隔(角度) 根据输入数据个数对应
    double m_txScaleInv;

    // 刻度文本列表
    QStringList m_txScaleList;

    // 最大最小刻度值
    double m_minVal, m_maxVal;

    // 当前刻度值
    double m_currentVal;

    // 当前刻度值对应角度
    double m_currentDeg;

    // 门限值
    double m_threshold;

    // 门限条件
    bool m_isLow;

    QString m_Unit;

protected:
    // 重写绘图事件
    void paintEvent(QPaintEvent* event) override;

    // 重写大小改变事件
    void resizeEvent(QResizeEvent* event) override;

    // 绘制刻度
    void drawScale(QPainter& painter);

    // 绘制弧线(扇面)
    void drawArc(QPainter& painter);
};

#endif // IR_INSTRUMENTPANEL_H
