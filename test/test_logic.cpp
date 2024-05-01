#include <gtest/gtest.h>

#include "iteration_extremum_finder.hpp"
#include "vec.hpp"
#include "matrix.hpp"
#include "danylevsky_matrix_eigen_vv.hpp"
#include "rotation_matrix_eigen_vv.hpp"
#include <iostream>
#include <thread>
#include <cmath>

using namespace std;

double fdanylevskogo(double x, const std::vector<double> & v)
{
    //x^(4)-6x^(3)+0.2x^(2)+12.735x-2.7616=0
    //Roots: -1.39687 0.220313 1.60625 5.56953 
    double res = pow(x, v.size());
    auto iter = v.rbegin();
    for (int i = 0; i < v.size(); i++, iter++)
    {
        res -= *iter * pow(x, i);
    }
    return res;
}

TEST(math, vec_basic_plus_positive){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = Vector({1, 2, 3});
    Vector v3 = v1 + v2;
    EXPECT_EQ(v3, Vector({2, 4, 6}));
}

TEST(math, vec_basic_plus_negative){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = Vector({1, 2, 3});
    Vector v3 = v1 + v2;
    EXPECT_NE(v3, Vector({1, 2, 3}));
}

TEST(math, vec_basic_minus_positive){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = Vector({1, 2, 3});
    Vector v3 = v1 - v2;
    EXPECT_EQ(v3, Vector({0, 0, 0}));
}

TEST(math, vec_basic_minus_negative){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = Vector({1, 2, 3});
    Vector v3 = v1 - v2;
    EXPECT_NE(v3, Vector({1, 2, 3}));
}

TEST(math, vec_basic_multiply_positive){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = Vector({1, 2, 3});
    double res = v1 * v2;
    EXPECT_EQ(res, 14);
}

TEST(math, vec_basic_multiply_negative){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = Vector({1, 2, 3});
    double res = v1 * v2;
    EXPECT_NE(res, 15);
}

TEST(math, vec_basic_multiply_scalar_positive){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = v1 * 2;
    EXPECT_EQ(v2, Vector({2, 4, 6}));
}

TEST(math, vec_basic_multiply_scalar_negative){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = v1 * 2;
    EXPECT_NE(v2, Vector({1, 2, 3}));
}

TEST(math, vec_basic_divide_scalar_positive){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = v1 / 2;
    EXPECT_EQ(v2, Vector({0.5, 1, 1.5}));
}

TEST(math, vec_basic_divide_scalar_negative){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = v1 / 2;
    EXPECT_NE(v2, Vector({1, 2, 3}));
}

TEST(math, vec_basic_plus_scalar_positive){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = v1 + 2;
    EXPECT_EQ(v2, Vector({3, 4, 5}));
}

TEST(math, vec_basic_plus_scalar_negative){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = v1 + 2;
    EXPECT_NE(v2, Vector({1, 2, 3}));
}

TEST(math, vec_basic_minus_scalar_positive){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = v1 - 2;
    EXPECT_EQ(v2, Vector({-1, 0, 1}));
}

TEST(math, vec_basic_minus_scalar_negative){
    Vector v1 = Vector({1, 2, 3});
    Vector v2 = v1 - 2;
    EXPECT_NE(v2, Vector({1, 2, 3}));
}

TEST(math, vec_basic_brackets_positive){
    Vector v1 = Vector({1, 2, 3});
    double res = v1[1];
    EXPECT_EQ(res, 2);
}

TEST(math, vec_basic_brackets_negative){
    Vector v1 = Vector({1, 2, 3});
    double res = v1[1];
    EXPECT_NE(res, 3);
}

TEST(math, vec_basic_brackets_const_positive){
    const Vector v1 = Vector({1, 2, 3});
    double res = v1[1];
    EXPECT_EQ(res, 2);
}

TEST(math, vec_basic_brackets_const_negative){
    const Vector v1 = Vector({1, 2, 3});
    double res = v1[1];
    EXPECT_NE(res, 3);
}

TEST(math, vec_basic_round_up_positive){
    Vector v1 = Vector({1.123456, 2.123456, 3.123456});
    Vector v2 = Vector({1.123, 2.123, 3.123});
    for ( int i = 0; i < v1.size(); ++i ){
        EXPECT_NEAR(v1[i], v2[i], 0.001);
    }
}

TEST(math, vec_basic_round_up_negative){
    Vector v1 = Vector({1.125, 2.123456, 3.123456});
    EXPECT_NE(v1, Vector({1.123456, 2.123456, 3.123456}));
}

TEST(math, vec_basic_size_positive){
    Vector v1 = Vector({1, 2, 3});
    int res = v1.size();
    EXPECT_EQ(res, 3);
}

TEST(math, vec_basic_size_negative){
    Vector v1 = Vector({1, 2, 3});
    int res = v1.size();
    EXPECT_NE(res, 4);
}

TEST(math, vec_basic_vector_positive){
    Vector v1 = Vector({1, 2, 3});
    std::vector<double> res = v1;
    EXPECT_EQ(res, std::vector<double>({1, 2, 3}));
}

TEST(math, vec_basic_vector_negative){
    Vector v1 = Vector({1, 2, 3});
    std::vector<double> res = v1;
    EXPECT_NE(res, std::vector<double>({1, 2, 3, 4}));
}

TEST(math, matrix_basic_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m3 = m1 + m2;
    EXPECT_EQ(m3, Matrix({Vector({2, 4, 6}), Vector({8, 10, 12}), Vector({14, 16, 18})}));
}

TEST(math, matrix_basic_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m3 = m1 + m2;
    EXPECT_NE(m3, Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})}));
}

TEST(math, matrix_basic_minus_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m3 = m1 - m2;
    EXPECT_EQ(m3, Matrix({Vector({0, 0, 0}), Vector({0, 0, 0}), Vector({0, 0, 0})}));
}

TEST(math, matrix_basic_minus_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m3 = m1 - m2;
    EXPECT_NE(m3, Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})}));
}

TEST(math, matrix_basic_multiply_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m3 = m1 * m2;
    EXPECT_EQ(m3, Matrix({Vector({30, 36, 42}), Vector({66, 81, 96}), Vector({102, 126, 150})}));
}

TEST(math, matrix_basic_multiply_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m3 = m1 * m2;
    EXPECT_NE(m3, Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})}));
}

TEST(math, matrix_basic_multiply_scalar_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = m1 * 2;
    EXPECT_EQ(m2, Matrix({Vector({2, 4, 6}), Vector({8, 10, 12}), Vector({14, 16, 18})}));
}

TEST(math, matrix_basic_multiply_scalar_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = m1 * 2;
    EXPECT_NE(m2, Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})}));
}

TEST(math, matrix_basic_divide_scalar_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = m1 / 2;
    EXPECT_EQ(m2, Matrix({Vector({0.5, 1, 1.5}), Vector({2, 2.5, 3}), Vector({3.5, 4, 4.5})}));
}

TEST(math, matrix_basic_divide_scalar_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = m1 / 2;
    EXPECT_NE(m2, Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})}));
}

TEST(math, matrix_basic_plus_scalar_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = m1 + 2;
    EXPECT_EQ(m2, Matrix({Vector({3, 4, 5}), Vector({6, 7, 8}), Vector({9, 10, 11})}));
}

TEST(math, matrix_basic_plus_scalar_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = m1 + 2;
    EXPECT_NE(m2, Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})}));
}

TEST(math, matrix_basic_minus_scalar_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = m1 - 2;
    EXPECT_EQ(m2, Matrix({Vector({-1, 0, 1}), Vector({2, 3, 4}), Vector({5, 6, 7})}));
}

TEST(math, matrix_basic_minus_scalar_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Matrix m2 = m1 - 2;
    EXPECT_NE(m2, Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})}));
}

TEST(math, matrix_basic_brackets_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Vector v = m1[1];
    EXPECT_EQ(v, Vector({4, 5, 6}));
}

TEST(math, matrix_basic_brackets_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Vector v = m1[1];
    EXPECT_NE(v, Vector({1, 2, 3}));
}

TEST(math, matrix_basic_brackets_const_positive){
    const Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Vector v = m1[1];
    EXPECT_EQ(v, Vector({4, 5, 6}));
}

TEST(math, matrix_basic_brackets_const_negative){
    const Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    Vector v = m1[1];
    EXPECT_NE(v, Vector({1, 2, 3}));
}

TEST(math, matrix_basic_rows_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    int res = m1.rows();
    EXPECT_EQ(res, 3);
}

TEST(math, matrix_basic_rows_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9})});
    int res = m1.rows();
    EXPECT_NE(res, 4);
}

TEST(math, matrix_basic_cols_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9}), Vector({10, 11, 12})});
    int res = m1.cols();
    EXPECT_EQ(res, 3);
}

TEST(math, matrix_basic_cols_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9}), Vector({10, 11, 12})});
    int res = m1.cols();
    EXPECT_NE(res, 4);
}

TEST(math, matrix_basic_transpose_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9}), Vector({10, 11, 12})});
    Matrix m2 = m1.transpose();
    EXPECT_EQ(m2, Matrix({Vector({1, 4, 7, 10}), Vector({2, 5, 8, 11}), Vector({3, 6, 9, 12})}));
}

TEST(math, matrix_basic_transpose_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9}), Vector({10, 11, 12})});
    Matrix m2 = m1.transpose();
    EXPECT_NE(m2, Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9}), Vector({10, 11, 12})}));
}

TEST(math, matrix_basic_brackets_matrix_positive){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9}), Vector({10, 11, 12})});
    Vector v = m1[1];
    EXPECT_EQ(v, Vector({4, 5, 6}));
}

TEST(math, matrix_basic_brackets_matrix_negative){
    Matrix m1 = Matrix({Vector({1, 2, 3}), Vector({4, 5, 6}), Vector({7, 8, 9}), Vector({10, 11, 12})});
    Vector v = m1[1];
    EXPECT_NE(v, Vector({1, 2, 3}));
}

TEST(math, test_danylevsky_class_positive){
    auto finder = std::make_unique<IterationExtremumFinder>(-1000, 1000, 0.001, 0.1);
    auto danylevsky = std::make_unique<DanylevskyMatrixEigenVV>(std::move(finder));
    std::vector<std::vector<double>> matrix = {
        {2.2,   1,      0.5,    2},
        {1,     1.3,    2,      1},
        {0.5,   2,      0.5,    1.6},
        {2,     1,      1.6,    2}
    };

   
    DanylevskyMatrixEigenVV::Result res = danylevsky->calculate(matrix);
    std::vector<double> expected = {-1.4201, 0.2226, 1.5454, 5.652};
    std::vector<std::vector<double>> v_expected = {
        {-0.6663, 1.548, -2.2723, 1},
        {-0.7402,-0.6451, 0.2176, 1},
        {3.1157, -2.8365, -2.4059, 1},
        {0.8975, 0.7531, 0.69, 1},

    };
    for (int i = 0; i < res.eigenValues.size(); i++){
        EXPECT_NEAR(res.eigenValues[i], expected[i], 0.01);
    }
    for (int i = 0; i < res.eigenVectors.size(); i++){
        for (int j = 0; j < res.eigenVectors[i].size(); j++){
            EXPECT_NEAR(res.eigenVectors[i][j], v_expected[i][j], 0.01);
        }
    }
}

TEST(math, test_danylevsky_class_an_eq_0){
    try {
        auto finder = std::make_unique<IterationExtremumFinder>(-1000, 1000, 0.001, 0.1);
        auto danylevsky = std::make_unique<DanylevskyMatrixEigenVV>(std::move(finder));
        std::vector<std::vector<double>> matrix = {
            {2.2, 1, 0.5, 2},
            {1, 1.3, 2, 1},
            {0.5, 2, 0.5, 1.6},
            {2, 1, 0, 2}
        };
        DanylevskyMatrixEigenVV::Result res = danylevsky->calculate(matrix);
    } catch (std::runtime_error &e) {
        EXPECT_STREQ(e.what(), "The element a[n][n-1] must not be equal to zero");
    }
}

TEST(math, test_rotation_matrix_basic){
    auto rotation = std::make_unique<RotationMatrixEigenVV>();
    std::vector<std::vector<double>> matrix = {
        {2.2,   1,      0.5,    2},
        {1,     1.3,    2,      1},
        {0.5,   2,      0.5,    1.6},
        {2,     1,      1.6,    2}
    };

   
    RotationMatrixEigenVV::Result res = rotation->calculate(matrix);
    std::vector<double> expected = {-1.4201, 0.2226, 1.5454, 5.652};
    std::vector<std::vector<double>> v_expected = {
        {-0.6663, 1.548, -2.2723, 1},
        {-0.7402,-0.6451, 0.2176, 1},
        {3.1157, -2.8365, -2.4059, 1},
        {0.8975, 0.7531, 0.69, 1},

    };
    for (int i = 0; i < res.eigenValues.size(); i++){
        EXPECT_NEAR(res.eigenValues[i], expected[i], 0.01);
    }
    for (int i = 0; i < res.eigenVectors.size(); i++){
        for (int j = 0; j < res.eigenVectors[i].size(); j++){
            EXPECT_NEAR(res.eigenVectors[i][j], v_expected[i][j], 0.01);
        }
    }
}

TEST(math, math_test_danylevsky_vs_rotation){
    //different square matrixes with different size
    vector<vector<vector<double>>> matrixs = {
        {
            {2.2,   1},
            {1,     1.3}
        },
        {
            {2.2,   1,      0.5},
            {1,     1.3,    2},
            {0.5,   2,      0.5}
        },
        {
            {2.2,   1,      0.5,    2},
            {1,     1.3,    2,      1},
            {0.5,   2,      0.5,    1.6},
            {2,     1,      1.6,    2}
        }
    };
    for (auto matrix : matrixs){
        auto finder = std::make_unique<IterationExtremumFinder>(-1000, 1000, 0.001, 0.1);
        auto danylevsky = std::make_unique<DanylevskyMatrixEigenVV>(std::move(finder));
        auto rotation = std::make_unique<RotationMatrixEigenVV>();
        auto res_danylevsky = danylevsky->calculate(matrix);
        auto res_rotation = rotation->calculate(matrix);
        for (int i = 0; i < res_danylevsky.eigenValues.size(); i++){
            EXPECT_NEAR(res_danylevsky.eigenValues[i], res_rotation.eigenValues[i], 0.01);
        }
        for (int i = 0; i < res_danylevsky.eigenVectors.size(); i++){
            for (int j = 0; j < res_danylevsky.eigenVectors[i].size(); j++){
                EXPECT_NEAR(res_danylevsky.eigenVectors[i][j], res_rotation.eigenVectors[i][j], 0.02);
            }
        }
    }
}

