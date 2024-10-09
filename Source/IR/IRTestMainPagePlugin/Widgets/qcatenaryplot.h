#ifndef QCATENARYPLOT_H
#define QCATENARYPLOT_H

//#pragma execution_character_set("utf-8")

#include "qcustomplot.h"
#include <QList>
#include <QMap>
#include <map>

class QCatenaryPlot : public QCustomPlot {
    Q_OBJECT
public:
    using QCPGraphMap     = std::map<int, QCPGraph*>;
    using QCPGraphList    = QList<QCPGraph*>;
    using QCPItemTextList = QList<QCPItemText*>;

    enum TextItemType {
        Pole,
        Dropper,
        Middle,
        Other,
        Sign
    };

    using TextMap = QMap<TextItemType, QCPItemTextList>;

public:
    QCatenaryPlot(QWidget* parent = nullptr);
    ~QCatenaryPlot();

public:
    void      ensureVisible(double x);
    void      addPoint(int lineId, double x, double y, QColor color = QColor(0, 0, 255));
    void      removeAll();
    QCPGraph* addCurve(const QVector<double>& x, const QVector<double>& y, QColor color = QColor(0, 0, 255));
    bool      removeCurve(QCPGraph* curve);

    void addDropperMarker(double x, double y);

    void addNonDropperMarker(double x, double y);
    void removeDropperMarker(double x);
    void removeNonDropperMarker(double x);
    void removeDropperMarkers();
    void removeDropperMarker(double x, double range);
    void removeDropperText(double x, double range);
    void removePoleText(double x, double range);

    void addXAxisTick(double x, const QString& label);
    void removeXAxisTick(double x);
    void removeXAxisTicks();

    void addYAxisTick(double x, const QString& label);
    void removeYAxisTicks();

    void removeRedundant();
    void removeRedundantText(TextItemType type = TextItemType::Other);
    void removeAfter(double x);
    void removeAfterText(double x, TextItemType type = TextItemType::Other);

    void generateYTicks();
    void addAuxiliaryLine(double y, QColor color = QColor(0, 0, 255));
    void addText(const QString& text, double x, double y, Qt::Alignment alignment,
                 TextItemType type = TextItemType::Other, QColor color = Qt::black, int padding = 5);
    void hideText(bool hide, TextItemType type = TextItemType::Other);
    bool textVisable(TextItemType type = TextItemType::Other);
    void clearText(TextItemType type = TextItemType::Other);
    void removeAuxiliaryLine();

    void generateOtherAuxiliaryLine();

    QCPRange getDataRange();

    void showPoleText(bool show = true);
    void showDropperText(bool show = true);
    void showMiddleText(bool show = true);

    void addText(double x, double y, const QString& text, double labelX, double labelY, TextItemType type = TextItemType::Other);

    void setMarkingLine(double x);
    void clearMarkingLine();

public slots:
    void setRange(double xMin, double xMax, double yMin, double yMax);

signals:
    //void rangeChanged(double xMin, double xMax, double yMin, double yMax);
    void showContextMenu(int x, int y, int globalX, int globalY);

private:
    QCPGraphMap                       m_graphMap;
    QCPGraphList                      m_graphList;
    QCPGraphList                      m_auxiliaryLines;
    QCPGraph*                         m_dropperGraph;
    QCPGraph*                         m_nonDropperGraph;
    QSharedPointer<QCPAxisTickerText> m_xAxisTextTicker;
    QSharedPointer<QCPAxisTickerText> m_yAxisTextTicker;
    QMap<double, QString>             m_xTickLabels;

    QCPRange m_dataRange;

    QCPGraph* m_MarkingLine;

    TextMap                  m_textMap;
    QMap<TextItemType, bool> m_textVisable;

    bool m_bShowPoleText;
    bool m_bShowDropperText;
    bool m_bShowMiddleText;

protected:
    virtual void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    virtual void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;
    virtual void contextMenuEvent(QContextMenuEvent* event) Q_DECL_OVERRIDE;
};

#endif // QCATENARYPLOT_H
