#include "matrix_model.hpp"

MatrixModel::MatrixModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

MatrixModel::~MatrixModel()
{
}

Qt::ItemFlags MatrixModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QModelIndex MatrixModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex MatrixModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int MatrixModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return matrix.size();
}

int MatrixModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (matrix.empty())
        return 0;

    return matrix[0].size();
}

QVariant MatrixModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return matrix[index.row()][index.column()];

    return QVariant();
}

bool MatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;
    double v = value.toDouble();
    if ( v > 1000 || v < -1000 || fabs(v) < 0.01)
        return false;
    matrix[index.row()][index.column()] = v;
    emit dataChanged(index, index, {role});
    return true;
}

QVariant MatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

void MatrixModel::setMatrix(const std::vector<std::vector<double>> &matrix)
{
    beginResetModel();
    this->matrix = matrix;
    endResetModel();
}

std::vector<std::vector<double>> MatrixModel::getMatrix() const
{
    return matrix;
}

// Path: qt_test/matrix_model.hpp