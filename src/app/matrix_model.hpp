#pragma once

#include <QAbstractItemModel>
#include <vector>

class MatrixModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    MatrixModel(QObject *parent = nullptr);
    ~MatrixModel();

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setMatrix(const std::vector<std::vector<double>> &matrix);
    std::vector<std::vector<double>> getMatrix() const;

private:
    std::vector<std::vector<double>> matrix;
};
