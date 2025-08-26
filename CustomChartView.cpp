#include "CustomChartView.h"
#include <QChart>

CustomChartView::CustomChartView(QWidget *parent) : QChartView(parent), m_isPanning(false)
{
    setRenderHint(QPainter::Antialiasing);
}

void CustomChartView::wheelEvent(QWheelEvent *event)
{
    QPointF p = event->position();
    qreal factor = 1.15;
    if (event->angleDelta().y() > 0) {
        chart()->zoom(factor);
    } else {
        chart()->zoom(1.0 / factor);
    }
    event->accept();
}

void CustomChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        m_isPanning = true;
        m_lastMousePos = event->pos();
        event->accept();
    }
    QChartView::mousePressEvent(event);
}

void CustomChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        QPointF delta = event->pos() - m_lastMousePos;
        chart()->scroll(-delta.x(), delta.y());
        m_lastMousePos = event->pos();
        event->accept();
    }
    QChartView::mouseMoveEvent(event);
}

void CustomChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        m_isPanning = false;
        event->accept();
    }
    QChartView::mouseReleaseEvent(event);
}
