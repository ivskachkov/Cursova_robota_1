#include "decart_graph_widget.h"
#include "utils.hpp"
#include <QPainter>

DecartGraphWidget::DecartGraphWidget(QWidget *parent) : QWidget(parent)
{
    minX = -10;
    maxX = 10;
    minY = -10;
    maxY = 10;
}

void DecartGraphWidget::showPolynom(const Result &result)
{
    if ( result.func == nullptr ){
        clear();
        return;
    }
    this->result = result;
    double value;
    this->stepX = calcStep(result.funcMaxX, &value);
    this->stepY = this->stepX*2;
    this->minX = -value;
    this->maxX = value;
    this->minY = this->minX;
    this->maxY = this->maxX;
    sHint = QSize(width(), width());
    updateGeometry();
    update();
    show();
}

QSize DecartGraphWidget::sizeHint() const
{
    return sHint;
}

void DecartGraphWidget::paintEvent(QPaintEvent *event)
{
    if (!result.func)
        return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);
    drawGrid(painter);
    drawPolynom(painter);
    drawAxis(painter);
    drawIntersections(painter);

    // painter.setPen(Qt::black);
    // painter.fillRect(0, 0, width(), 20, Qt::white);
    // painter.drawText(5, 15, formula(result));
}

//Convert x to screen coordinate and center them
double DecartGraphWidget::xToScreen(double x)
{
    double range = maxX - minX;
    return (x - minX) * width() / range;
}

double DecartGraphWidget::yToScreen(double y)
{
    return height() - (y - minY) * height() / (maxY - minY);
}

void DecartGraphWidget::drawGrid(QPainter &painter)
{
    for (double x = minX, half = x + stepX/2; x <= maxX; x += stepX, half += stepX) {
        painter.setPen(Qt::lightGray);
        painter.drawLine(xToScreen(x), 0, xToScreen(x), height());
        painter.setPen(QColor(0, 0, 0, 15));
        painter.drawLine(xToScreen(half), 0, xToScreen(half), height());
        if ( fabs(x) < 1e-4)
            continue;
        painter.setPen(Qt::black);
        painter.drawText(xToScreen(x) + 8, yToScreen(0) - 8,  QString::asprintf("%.2f ", x));
    }
    double yStart = xToScreen(minX);
    double eEnd = xToScreen(maxX);
    for (double y = minY, half = y + stepY/2; y <= maxY; y += stepY, half += stepY) {
        painter.setPen(Qt::lightGray);
        painter.drawLine(yStart, yToScreen(y), eEnd, yToScreen(y));
        painter.setPen(QColor(0, 0, 0, 15));
        painter.drawLine(yStart, yToScreen(half), eEnd, yToScreen(half));
        if ( fabs(y) < 1e-4)
            continue;
        painter.setPen(Qt::black);
        painter.drawText(xToScreen(0) + 8, yToScreen(y) - 8, QString::asprintf("%.2f ", y));
    }
}

void DecartGraphWidget::drawPolynom(QPainter &painter)
{
    painter.setPen(Qt::blue);
    double step = (maxX - minX) / 1000;
    for (double x = minX; x < maxX; x += step) {
        double y = result.func(x);
        painter.drawLine(xToScreen(x), yToScreen(y), xToScreen(x + step), yToScreen(result.func(x + step)));
    }
}

void DecartGraphWidget::drawAxis(QPainter &painter)
{
    painter.setPen(Qt::black);
    painter.drawLine(xToScreen(0), 0, xToScreen(0), height());
    painter.drawLine(0, yToScreen(0), width(), yToScreen(0));
}

void DecartGraphWidget::drawIntersections(QPainter &painter)
{
    static const int radius = 3;
    painter.setPen(Qt::red);
    painter.setBrush(Qt::white);
    for (auto ee : result.data) {
        painter.drawEllipse(xToScreen(ee.eigenValue) - radius, yToScreen(0) - radius, 2 * radius, 2 * radius);
    }
}

void DecartGraphWidget::clear()
{
    result = Result();
    updateGeometry ();
    update();
}
