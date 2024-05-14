#include "window.h"
#include "ui_window.h"
#include <QDebug>
#include <QFileDialog>
#include <fstream>
#include <stdexcept>

#include "../logic/eigen_finder.h"

static std::ostream & operator<<(std::ostream & os, const std::vector<std::vector<double>> & matrix)
{
    os << matrix.size() << '\n';
    for (const auto & row : matrix) {
        for (double value : row)
            os << value << ' ';
        os << '\n';
    }
    return os;
}

static std::istream & operator>>(std::istream & is, std::vector<std::vector<double>> & matrix)
{
    size_t size;
    is >> size;
    matrix.resize(size);
    for (auto & row : matrix) {
        row.resize(size);
        for (double & value : row)
            is >> value;
    }
    return is;
}

template<typename T>
std::string to_string(const std::vector<T> & v)
{
    std::string result;
    for (const T & value : v){
        if (!result.empty())
            result += ", ";
        result += std::to_string(value);
    }
    return "{" + result + "}";
}

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
    , matrixModel(new MatrixModel(this))
{
    ui->setupUi(this);
    ui->initMatrixTableView->setModel(matrixModel);
    
    std::vector<std::vector<double>> matrix(4);
    matrix[0] = std::vector<double>{2.2, 1, 0.5, 2};
    matrix[1] = std::vector<double>{1, 1.3, 2, 1};
    matrix[2] = std::vector<double>{0.5, 2, 0.5, 1.6};
    matrix[3] = std::vector<double>{2, 1, 1.6, 2};

    matrixModel->setMatrix(matrix);
    connect(matrixModel, &MatrixModel::dataChanged, this, [this](){
        this->on_calculateButton_clicked();
    });
    connect(matrixModel, &MatrixModel::modelReset, this, [this](){
        auto state = ui->matrixSizeSpinBox->blockSignals(true);
        ui->matrixSizeSpinBox->setValue(matrixModel->rowCount());
        ui->matrixSizeSpinBox->blockSignals(state);
        this->on_calculateButton_clicked();
    });
}

Window::~Window()
{
    delete ui;
}

void Window::on_matrixSizeSpinBox_valueChanged(int v)
{
    std::vector<std::vector<double>> matrix(v, std::vector<double>(v, 0));
    for (int i = 0; i < v; ++i)
        for (int j = 0; j < v; ++j)
            matrix[i][j] = i == j ? 1 : 0;
    matrixModel->setMatrix(matrix);
}

void Window::on_methodComboBox_textActivated(const QString &text)
{
    ui->statusbar->showMessage("Method: " + text, 3000);
}

void Window::on_actionOpen_triggered()
{
    auto fileName = QFileDialog::getOpenFileName(this, "Open file", "", "Text files (*.txt)");
    if (fileName.isEmpty())
        return;
    std::ifstream file(fileName.toStdString());
    std::vector<std::vector<double>> matrix;
    if ( file >> matrix ){
        matrixModel->setMatrix(matrix);
        ui->statusbar->showMessage("File: '" + fileName + "' loaded", 10000);
    } else 
        qDebug() << "Cannot load file: " << fileName;
    file.close();
}

void Window::on_actionSave_triggered()
{
    auto fileName = QFileDialog::getSaveFileName(this, "Save file", "", "Text files (*.txt)");
    if (fileName.isEmpty())
        return;
    std::ofstream file(fileName.toStdString());
    if ( file << matrixModel->getMatrix() ){
        ui->statusbar->showMessage("File: '" + fileName + "' saved", 10000);
    } else
        qDebug() << "Cannot save file: " << fileName;
    file.close();
}

void Window::on_calculateButton_clicked()
{
    try {
        ui->graph->clear();
        if (ui->methodComboBox->currentText() == "Danylevskogo"){
            eigenVV = createDanylevskyMatrixEigenVV();
            auto matrix = matrixModel->getMatrix();
            if (eigenVV) {
                QString text;
                auto results = eigenVV->calculate(matrix);
                for (int i = 0; i < results.data.size(); ++i) {
                    if ( results.data.size() > i ){
                        text += "Eigen value: " + QString::number(results.data[i].eigenValue) + " \t";
                    }
                    if ( results.data.size() > i ){
                        text += "Vector: " + QString::fromStdString(to_string(results.data[i].eigenVector));
                    }
                    text += "\n";
                }
                ui->lblResult->setText(text);
                ui->graph->showPolynom(results);
            }
        }
        else if (ui->methodComboBox->currentText() == "Rotation"){
            eigenVV = createRotationMatrixEigenVV();
            auto matrix = matrixModel->getMatrix();
            if (eigenVV) {
                QString text;
                auto results = eigenVV->calculate(matrix);
                for (int i = 0; i < results.data.size(); ++i) {
                    if ( results.data.size() > i ){
                        text += "Eigen value: " + QString::number(results.data[i].eigenValue) + " \t";
                    }
                    if ( results.data.size() > i ){
                        text += "Vector: " + QString::fromStdString(to_string(results.data[i].eigenVector));
                    }
                    text += "\n";
                }
                ui->lblResult->setText(text);
            }
        }
    } catch (const std::exception & e) {
        ui->lblResult->setText("");
        ui->graph->clear();
        ui->statusbar->showMessage("This method could not be used for the matrix because: " + QString(e.what()), 10000);
    }
}
