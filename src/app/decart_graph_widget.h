#pragma once 

#include <QWidget>
#include "matrix_eigen_vv.hpp"

//Widget to show a decart graph
class DecartGraphWidget : public QWidget
{
    Q_OBJECT
public:
    using Result = IMatrixEigenVV::Result;
    explicit DecartGraphWidget(QWidget *parent = nullptr);
    void showPolynom(const Result & result);
    QSize sizeHint() const override;
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Result result;
    double minX, maxX, minY, maxY;
    double stepX, stepY;
    double scaleX, scaleY;
    double offsetX, offsetY;
    QSize sHint;
    double xToScreen(double x);
    double yToScreen(double y);
    void drawGrid(QPainter &painter);
    void drawPolynom(QPainter &painter);
    void drawAxis(QPainter &painter);
    void drawIntersections(QPainter &painter);
    static QString formula(const Result & result);
};