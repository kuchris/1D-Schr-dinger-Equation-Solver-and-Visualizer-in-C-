#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QMouseEvent>
#include <QWheelEvent>

QT_CHARTS_USE_NAMESPACE

class CustomChartView : public QChartView
{
    Q_OBJECT
public:
    explicit CustomChartView(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint m_lastMousePos;
    bool m_isPanning;
};

#endif // CUSTOMCHARTVIEW_H
