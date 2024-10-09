#include "qcatenaryplot.h"
#include <QVector>


QCatenaryPlot::QCatenaryPlot(QWidget* parent)
    :QCustomPlot(parent)
{

    setInteractions(/*QCP::iRangeDrag |*/ QCP::iRangeZoom);
    axisRect()->setRangeZoom(Qt::Horizontal);
    //axisRect()->setRangeDrag(Qt::Horizontal);

    xAxis2->setVisible(true);
    yAxis2->setVisible(true);
    xAxis2->setTicks(false);
    yAxis2->setTicks(false);
    xAxis2->setTickLabels(false);
    yAxis2->setTickLabels(false);

    m_dropperGraph = addGraph();
    QCPScatterStyle style(QCPScatterStyle::ssDot,6);
    m_dropperGraph->setScatterStyle(style);
    QPen pen;
    pen.setWidth(4);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(0, 0, 255));
    m_dropperGraph->setPen(pen);
    m_dropperGraph->setLineStyle(QCPGraph::lsNone);

    m_nonDropperGraph = addGraph();
    m_nonDropperGraph->setScatterStyle(style);
    pen.setColor(QColor(0, 0, 255));
    m_nonDropperGraph->setPen(pen);
    m_nonDropperGraph->setLineStyle(QCPGraph::lsNone);

    m_xAxisTextTicker = QSharedPointer<QCPAxisTickerText>(new QCPAxisTickerText());
    xAxis->setTicker(m_xAxisTextTicker);


    QPen linePen;
    linePen.setWidth(1);
    linePen.setColor(QColor(255,0,0));
    linePen.setStyle(Qt::SolidLine);
    m_MarkingLine = addGraph();
    m_MarkingLine->setPen(linePen);

    //setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    m_bShowPoleText = false;
    m_bShowDropperText = false;
    m_bShowMiddleText = false;

    m_textVisable[Pole] = true;
    m_textVisable[Dropper] = true;
    m_textVisable[Middle] = true;
    m_textVisable[Other] = true;
    m_textVisable[Sign] = true;

}

QCatenaryPlot::~QCatenaryPlot()
{
    removeAll();
}

void QCatenaryPlot::setMarkingLine(double x)
{
    m_MarkingLine->addData(x, -1000000);
    m_MarkingLine->addData(x, 1000000);
}

void QCatenaryPlot::clearMarkingLine()
{
    m_MarkingLine->setData(QVector<double>(), QVector<double>());
}

void QCatenaryPlot::ensureVisible(double x)
{
    QCPRange range = this->xAxis->range();
    double size = range.size();
    double temp = size * 0.1;
    if( x < range.lower)
    {
        range.lower = x - temp;
        range.upper = range.lower + size;
        xAxis->setRange(range);

    }
    else if(x > range.upper)
    {
        range.upper = x + temp;
        range.lower = range.upper - size;
        xAxis->setRange(range);
    }
}

void QCatenaryPlot::addPoint(int lineId, double x, double y, QColor color)
{
    QCPGraphMap::iterator _it = m_graphMap.find(lineId);
    QCPGraph* pGraph = nullptr;
    if(_it == m_graphMap.end())
    {
        pGraph = this->addGraph();
        QPen pen;
        pen.setWidth(1);
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pGraph->setPen(pen);
        m_graphMap.insert(std::make_pair(lineId, pGraph));
    }else
    {
        pGraph = _it->second;
    }
    pGraph->addData(x, y);

    QCPRange range = xAxis->range();
    pGraph->data()->removeBefore(range.lower - 1);
    pGraph->data()->removeAfter(range.upper + 1);
}

QCPGraph*  QCatenaryPlot::addCurve(const QVector<double>& x, const QVector<double>& y, QColor color)
{
    QCPGraph* graph = addGraph();
    QPen pen;
    pen.setWidth(1);
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    graph->setPen(pen);

    graph->setData(x, y);

    m_graphList.push_back(graph);
    m_dataRange = getDataRange();

    return graph;
}

bool QCatenaryPlot::removeCurve(QCPGraph* curve)
{
    this->removeGraph(curve);
    return m_graphList.removeOne(curve);
}

void QCatenaryPlot::removeAll()
{
    for(QCPGraphMap::iterator it = m_graphMap.begin(); it != m_graphMap.end(); it++)
    {
        this->removeGraph(it->second);
    }

    for (QCPGraphList::iterator it = m_graphList.begin(); it != m_graphList.end(); it++)
    {
        this->removeGraph(*it);
    }

    clearText(TextItemType::Pole);
    clearText(TextItemType::Middle);
    clearText(TextItemType::Dropper);

    m_graphList.clear();
    m_graphMap.clear();
    removeDropperMarkers();
    removeXAxisTicks();
}

void QCatenaryPlot::addDropperMarker(double x, double y)
{
    m_dropperGraph->addData(x, y);
}

void QCatenaryPlot::addNonDropperMarker(double x, double y)
{
    m_nonDropperGraph->addData(x, y);
}

void QCatenaryPlot::removeDropperMarkers()
{
    QVector<double> x;
    QVector<double> y;
    m_dropperGraph->setData(x, y);
    m_nonDropperGraph->setData(x, y);
}

void QCatenaryPlot::removeDropperMarker(double x)
{
    m_dropperGraph->data()->remove(x);
}

void QCatenaryPlot::removeNonDropperMarker(double x)
{
    m_nonDropperGraph->data()->remove(x);
}

void QCatenaryPlot::removeDropperMarker(double x, double range)
{
    m_dropperGraph->data()->remove(x - range, x + range);
}

void QCatenaryPlot::removeDropperText(double x, double range)
{
     QCPItemTextList& texts = m_textMap[TextItemType::Dropper];

     for(int i = 0; i < texts.size(); i++)
     {
         QCPItemText* text = texts[i];
         if(text->position->coords().x() >= x- range
                 && text->position->coords().x() <= x + range )
         {
             removeItem(text);
             texts.removeAt(i);
             return;
         }
     }
}

void QCatenaryPlot::removePoleText(double x, double range)
{
    QCPItemTextList& texts = m_textMap[TextItemType::Pole];

    for(int i = 0; i < texts.size(); i++)
    {
        QCPItemText* text = texts[i];
        if(text->position->coords().x() >= x- range
                && text->position->coords().x() <= x + range )
        {
            removeItem(text);
            texts.removeAt(i);
            return;
        }
    }
}


void QCatenaryPlot::addXAxisTick(double x, const QString& label)
{
    m_xAxisTextTicker->addTick(x, label);
    m_xTickLabels.insert(x, label);
}

void QCatenaryPlot::removeXAxisTick(double x)
{
    m_xAxisTextTicker->clear();
    m_xTickLabels.remove(x);
    m_xAxisTextTicker->addTicks(m_xTickLabels);
}

void QCatenaryPlot::removeXAxisTicks()
{
    m_xAxisTextTicker->clear();
    m_xTickLabels.clear();
}

void QCatenaryPlot::addYAxisTick(double x, const QString& label)
{
    if (m_yAxisTextTicker.isNull())
    {
        m_yAxisTextTicker = QSharedPointer<QCPAxisTickerText>(new QCPAxisTickerText());
        yAxis->setTicker(m_yAxisTextTicker);
    }

    m_yAxisTextTicker->addTick(x, label);
}

void QCatenaryPlot::removeYAxisTicks()
{
    if(!m_yAxisTextTicker.isNull())
        m_yAxisTextTicker->clear();
}


void QCatenaryPlot::setRange(double xMin, double xMax, double yMin, double yMax)
{
    xAxis->setRange(xMin, xMax);
    yAxis->setRange(yMin, yMax);
}

//移除显示范围外的曲线
void QCatenaryPlot::removeRedundant()
{
    QCPRange xrange = xAxis->range();
    double xMin = xrange.lower - xrange.size() * 0.1;
    double xMax = xrange.upper + xrange.size() * 0.1;
    bool bFoundRange;
    for(QCPGraphMap::iterator it = m_graphMap.begin(); it != m_graphMap.end();)
    {
        QCPRange range = it->second->getKeyRange(bFoundRange);
        if(bFoundRange &&
                (range.upper < xMin || range.lower > xMax))
        {
            removeGraph(it->second);
            it = m_graphMap.erase(it);
        }
        else
        {
            it++;
        }
    }

    removeAfterText(Pole);
    removeAfterText(Dropper);
    removeAfterText(Middle);
}

void QCatenaryPlot::removeRedundantText(QCatenaryPlot::TextItemType type)
{
    QCPRange xrange = xAxis->range();
    double xMin = xrange.lower - xrange.size() * 0.1;
    double xMax = xrange.upper + xrange.size() * 0.1;

    QCPItemTextList& textItems = m_textMap[type];
    for (QCPItemTextList::iterator it = textItems.begin(); it != textItems.end(); )
    {
        if((*it)->position->coords().x() < xMin
                ||(*it)->position->coords().x() >xMax )
        {
            removeItem(*it);
            it = textItems.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void QCatenaryPlot::removeAfter(double x)
{
    m_dropperGraph->data()->removeAfter(x);

    QMap<double, QString>::iterator it_tick = m_xTickLabels.upperBound(x);
    if(it_tick != m_xTickLabels.end())
    {
        while(it_tick != m_xTickLabels.end())
        {
            it_tick = m_xTickLabels.erase(it_tick);
        }
        m_xAxisTextTicker->clear();
        if(!m_xTickLabels.empty())
            m_xAxisTextTicker->addTicks(m_xTickLabels);
    }

    for(QCPGraphMap::iterator it = m_graphMap.begin(); it != m_graphMap.end(); )
    {
        it->second->data()->removeAfter(x);
        if(it->second->data()->isEmpty())
        {
            removeGraph(it->second);
            it = m_graphMap.erase(it);
        }
        else
        {
            it++;
        }
    }

    removeAfterText(x, Pole);
    removeAfterText(x, Dropper);
    removeAfterText(x, Middle);
}

void QCatenaryPlot::removeAfterText(double x, QCatenaryPlot::TextItemType type)
{
    QCPItemTextList& textItems = m_textMap[type];
    for (QCPItemTextList::iterator it = textItems.begin(); it != textItems.end(); )
    {
        if((*it)->position->coords().x() >= x)
        {
            removeItem(*it);
            it = textItems.erase(it);
        }
        else
        {
            it++;
        }
    }

}

void QCatenaryPlot::addAuxiliaryLine(double y, QColor color)
{
    QCPGraph* graph = addGraph();
    QPen pen;
    pen.setWidth(1);
    pen.setColor(color);
    pen.setStyle(Qt::DashLine);
    graph->setPen(pen);

    double max_dist = std::numeric_limits<double>::min();
    double min_dist = std::numeric_limits<double>::max();

    graph->addData(-100000000.0, y);
    graph->addData(100000000.0, y);

    m_auxiliaryLines.push_back(graph);
}

void QCatenaryPlot::addText(const QString& text, double x, double y, Qt::Alignment alignment,\
    TextItemType type, QColor color, int padding)
{
    QCPItemText *phaseTracerText = new QCPItemText(this);
    if (type == Sign)
    {
        phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
    }
    else
    {
        phaseTracerText->position->setType(QCPItemPosition::ptPlotCoords);
    }

    phaseTracerText->setPositionAlignment(alignment);
    phaseTracerText->position->setCoords(x, y); // lower right corner of axis rect

    phaseTracerText->setText(text);
    phaseTracerText->setTextAlignment(Qt::AlignLeft);
    QFont f(font().family(), 9);
    phaseTracerText->setFont(f);
    //QPen pen = phaseTracerText->pen();
    //pen.setColor(color);
    //phaseTracerText->setPen(pen);
    phaseTracerText->setColor(color);
    phaseTracerText->setPadding(QMargins(padding, padding, padding, padding));

    if(!m_textVisable[type])
    {
        phaseTracerText->setVisible(false);
    }

    m_textMap[type].push_back(phaseTracerText);
}

void QCatenaryPlot::generateYTicks()
{
    QCPRange range = yAxis->range();
    int step = (range.upper - range.lower) / 8;

    if (step < 100)
        step = (step / 10) * 10 + ((step % 10 > 4) ? 10 : 0);
    else if(step >= 100)
        step = (step / 100) * 100 + ((step % 100 > 4) ? 100 : 0);

    int n = qFloor((range.upper - range.lower) / step);
    range.lower = range.lower + (range.upper - range.lower - n * step) / 2;

    for (int i = 0; i < n; i++)
    {
        bool iscontinue = false;;
        double y = i * step + range.lower;
        QCPGraph* graph;
        foreach(graph, m_auxiliaryLines)
        {
            if (fabs(y - graph->dataMainValue(0)) < step / 2)
            {
                iscontinue = true;
                break;
            }
        }
        if (iscontinue) continue;
        addAuxiliaryLine(y, QColor(194, 194, 194));
        addYAxisTick(y, QString::number((int)y));
    }
}

void QCatenaryPlot::clearText(TextItemType type)
{
    QCPItemTextList& textItems = m_textMap[type];
    for (QCPItemTextList::iterator it = textItems.begin(); it != textItems.end(); it++)
    {
        this->removeItem(*it);
    }
    m_textMap.remove(type);
}

void QCatenaryPlot::hideText(bool hide, TextItemType type)
{
    QCPItemTextList& textItems = m_textMap[type];
    for (QCPItemTextList::iterator it = textItems.begin(); it != textItems.end(); it++)
    {
        (*it)->setVisible(!hide);
    }
    m_textVisable[type] = !hide;
}

bool QCatenaryPlot::textVisable(QCatenaryPlot::TextItemType type)
{
    return m_textVisable[type];
}

void QCatenaryPlot::removeAuxiliaryLine()
{
    QCPGraph* graph;
    foreach (graph, m_auxiliaryLines)
    {
        removeGraph(graph);
    }
    m_auxiliaryLines.clear();
    if(!m_yAxisTextTicker.isNull())
        m_yAxisTextTicker->clear();
}

QCPRange QCatenaryPlot::getDataRange()
{
    QCPRange result(0, 0);
    QCPGraph* graph;
    bool findRange;
    foreach(graph, m_graphList)
    {
        QCPRange range = graph->getKeyRange(findRange);
        if (findRange)
        {
            if (result.upper == result.lower)
            {
                result = range;
            }
            else
            {
                if (range.lower < result.lower)
                    result.lower = range.lower;
                if (range.upper > result.upper)
                    result.upper = range.upper;
            }
        }
    }
    return result;
}

void QCatenaryPlot::showPoleText(bool show)
{

}

void QCatenaryPlot::showDropperText(bool show)
{

}

void QCatenaryPlot::showMiddleText(bool show)
{

}

void QCatenaryPlot::addText(double x, double y, const QString& text, double labelX, double labelY,\
                             TextItemType type)
{
    QCPItemText* textLabel = new QCPItemText(this);//在QCustomplot中新建文字框
    //QCPItemLine* arrow = new QCPItemLine(this);
    QPen pen;
    pen.setStyle(Qt::PenStyle::DashDotLine);
    //arrow->setPen(pen);
    textLabel->position->setType(QCPItemPosition::ptPlotCoords);//位置类型（当前轴范围的比例为单位/实际坐标为单位）
    textLabel->position->setCoords(labelX, labelY); //把文字框放在X轴的中间，Y轴的最顶部

    Qt::Alignment alignment = 0;

    if (labelX < x)
    {
        textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignLeft | Qt::AlignVCenter);//文字布局：顶、左对齐
        //arrow->start->setParentAnchor(textLabel->left);  //设置该直线的起点为文字框的下锚点
    }
    else if (labelX > x)
    {
        textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignRight | Qt::AlignVCenter);//文字布局：顶、左对齐
        //arrow->start->setParentAnchor(textLabel->right);  //设置该直线的起点为文字框的下锚点
    }
    else if (labelY > y)
    {
        textLabel->setPositionAlignment(Qt::AlignBottom | Qt::AlignHCenter);//文字布局：顶、左对齐
        //arrow->start->setParentAnchor(textLabel->bottom);  //设置该直线的起点为文字框的下锚点
    }
    else
    {
        textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);//文字布局：顶、左对齐
        //arrow->start->setParentAnchor(textLabel->top);  //设置该直线的起点为文字框的下锚点
    }

    textLabel->setText(text);
    textLabel->setFont(QFont(font().family(), 10)); //字体大小
    textLabel->setPen(QPen(Qt::black)); //字体颜色
    textLabel->setPadding(QMargins(2, 2, 2, 2));//文字距离边框几个像素

    m_textMap[type].push_back(textLabel);

    if(!m_textVisable[type])
    {
        textLabel->setVisible(false);
    }

    //arrow->end->setCoords(x, y); //设置直线终点为坐标系中的点
    //arrow->setHead(QCPLineEnding::esSpikeArrow);//设置箭头类型（三角形、菱形、方形等）
    //arrow->setVisible(true);
}

void QCatenaryPlot::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QCPRange range = xAxis->range();
        QPoint move = mMousePressPos - event->pos();

        if (move.x() > 0)
        {
            if (m_dataRange.upper - (range.upper - range.lower) / 10 < range.lower)
            {
                QCP::Interactions interactions = this->interactions();
                setInteractions(interactions & (~QCP::iRangeDrag));
            }
            else
            {
                QCP::Interactions interactions = this->interactions();
                setInteractions(interactions | QCP::iRangeDrag);
            }
        }
        else if (move.x() < 0)
        {
            if (m_dataRange.lower + (range.upper - range.lower) / 10 > range.upper)
            {
                QCP::Interactions interactions = this->interactions();
                setInteractions(interactions & (~QCP::iRangeDrag));
            }
            else
            {
                QCP::Interactions interactions = this->interactions();
                setInteractions(interactions | QCP::iRangeDrag);
            }
        }
    }
    QCustomPlot::mouseMoveEvent(event);
}
void QCatenaryPlot::wheelEvent(QWheelEvent *event)
{
    int numDegress = event->delta();
    QCPRange range = xAxis->range();
    if (numDegress < 0)
    {
        if (range.upper - range.lower > 1000
            || range.upper - range.lower > m_dataRange.upper - m_dataRange.lower)
        {
            QCP::Interactions interactions = this->interactions();
            setInteractions(interactions & (~QCP::iRangeZoom));
        }
        else
        {
            QCP::Interactions interactions = this->interactions();
            setInteractions(interactions | QCP::iRangeZoom);
        }
    }
    else
    {
        QCP::Interactions interactions = this->interactions();
        setInteractions(interactions | QCP::iRangeZoom);
    }

    QCustomPlot::wheelEvent(event);
}

void QCatenaryPlot::contextMenuEvent(QContextMenuEvent *event)
{
    event->accept();
    emit showContextMenu(event->x(), event->y(), event->globalX(), event->globalY());
}
