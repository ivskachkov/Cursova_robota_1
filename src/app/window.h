#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QLineSeries>
#include "matrix_model.hpp"
#include <matrix_eigen_vv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window(QWidget *parent = nullptr);
    ~Window();
    
private slots:
    void on_matrixSizeSpinBox_valueChanged(int value);
    void on_methodComboBox_textActivated(const QString &text);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_calculateButton_clicked();

private:
    Ui::Window *ui;
    MatrixModel * matrixModel;
    std::unique_ptr<IMatrixEigenVV> eigenVV;
    QLineSeries * series;
};

#endif // WINDOW_H
