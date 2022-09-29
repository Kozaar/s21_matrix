#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <iostream>
#include <math.h>

class S21Matrix {
    friend S21Matrix operator*(const double num, const S21Matrix& o);

 private:
        int _rows, _cols;
        double **matrix;

        void recreate_matrix(int rows, int cols);
        S21Matrix minor_matrix(int k, int l);
        void delete_matrix();

 public:
        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other);
        ~S21Matrix();
        bool eq_matrix(const S21Matrix& other);
        void sum_matrix(const S21Matrix& other);
        void sub_matrix(const S21Matrix& other);
        void mul_number(const double num);
        void mul_matrix(const S21Matrix& other);
        S21Matrix transpose();
        S21Matrix calc_complements();
        double determinant();
        S21Matrix inverse_matrix();

        S21Matrix operator+(const S21Matrix& o);
        S21Matrix operator-(const S21Matrix& o);
        S21Matrix operator*(const S21Matrix& o);
        S21Matrix operator*(const double num);
        bool operator==(const S21Matrix& o);
        S21Matrix& operator=(const S21Matrix& o);
        S21Matrix& operator+=(const S21Matrix& o);
        S21Matrix& operator-=(const S21Matrix& o);
        S21Matrix& operator*=(const S21Matrix& o);
        S21Matrix& operator*=(const double num);

        double& operator()(int row, int col);
        double& operator()(int row, int col) const;

        int get_rows() const;
        int get_cols() const;
        void set_rows(int rows);
        void set_cols(int cols);
};

#endif  //  SRC_S21_MATRIX_OOP_H_
