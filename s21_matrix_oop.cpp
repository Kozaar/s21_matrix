#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
    _rows = 3;
    _cols = 3;
    matrix = new double*[_rows];
    for (int i = 0; i < _rows; i++) {
        matrix[i] = new double[_cols];
        for (int j = 0; j < _cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

S21Matrix::S21Matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Incorrect input, index must be > 0");
    } else {
        _rows = rows;
        _cols = cols;
        matrix = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new double[cols];
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = 0;
            }
        }
    }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    if (other.matrix == NULL)
        throw std::out_of_range("Incorrect matrix");
    _rows = other._rows;
    _cols = other._cols;
    matrix = new double*[_rows];
    for (int i = 0; i < _rows; i++) {
        matrix[i] = new double[_cols];
        for (int j = 0; j < _cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    if (other.matrix == NULL)
        throw std::out_of_range("Incorrect matrix");
    _rows = other._rows;
    _cols = other._cols;
    matrix = other.matrix;
    other.matrix = NULL;
    other._rows = 0;
    other._cols = 0;
}

S21Matrix::~S21Matrix() {
    delete_matrix();
}

bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool res = true;
    if (_rows == other._rows && _cols == other._cols) {
        for (int i = 0; res == true && i < _rows; i++) {
            for (int j= 0; res == true && j < _cols; j++) {
                if (matrix[i][j] != other.matrix[i][j]) {
                    res = false;
                }
            }
        }
    } else {
        res = false;
    }
    return res;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (_rows != other._rows || _cols != other. _cols) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else if (_rows <= 0 || _cols <= 0) {
        throw std::out_of_range("Incorrect matrices");
    } else {
        for (int i = 0; i < _rows && matrix[i] != NULL && other.matrix[i] != NULL; i++) {
            for (int j = 0; j < _cols; j++) {
                matrix[i][j] += other.matrix[i][j];
            }
        }
    }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (_rows != other._rows || _cols != other. _cols) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    }
    if (_rows <= 0 || _cols <= 0) {
        throw std::out_of_range("Incorrect matrices");
    }
    for (int i = 0; i < _rows && matrix[i] != NULL && other.matrix[i] != NULL; i++) {
        for (int j = 0; j < _cols; j++) {
            matrix[i][j] -= other.matrix[i][j];
        }
    }
}

void S21Matrix::mul_number(const double num) {
    if (num != num)
        throw std::invalid_argument("Incorrect input: not a number");
    if (matrix == NULL)
        throw std::out_of_range("Incorrect matrix");
    for (int i = 0; i < _rows && matrix[i] != NULL; i++) {
        for (int j = 0; j < _cols; j++) {
            matrix[i][j] *= num;
        }
    }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (_cols != other._rows)
        throw std::invalid_argument("Incorrect input: num of cols 1st matrix != num of rows 2nd matrix");
    if (matrix == NULL)
        throw std::out_of_range("Incorrect matrix");
    S21Matrix res(*this);
    recreate_matrix(res._rows, other._cols);
    for (int i = 0; i < res._rows; i++) {
        for (int j = 0; j < other._cols; j++) {
            for (int k = 0; k < res._cols; k++) {
                matrix[i][j] += res.matrix[i][k] * other.matrix[k][j];
            }
        }
    }
}

S21Matrix S21Matrix::transpose() {
    if (_cols <= 0 || _rows <= 0 || matrix == NULL)
        throw std::out_of_range("Incorrect matrix");
    S21Matrix res(_cols, _rows);
    for (int i = 0; i < _cols; i++) {
        for (int j = 0; j < _rows; j++) {
            res.matrix[i][j] = matrix[j][i];
        }
    }
    return res;
}

S21Matrix S21Matrix::calc_complements() {
    if (_rows != _cols)
         throw std::invalid_argument("Incorrect input: the matrix is not square");
    if (_cols <= 0 || matrix == NULL)
        throw std::out_of_range("Incorrect matrix");
    S21Matrix res(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            S21Matrix M(minor_matrix(i, j));
            res.matrix[i][j] = pow(-1, i+j) * M.determinant();
            M.delete_matrix();
        }
    }
    return res;
}

double S21Matrix::determinant() {
    if (_rows != _cols)
        throw std::invalid_argument("Incorrect input: the matrix is not square");
    if (_cols <= 0 || matrix == NULL)
        throw std::out_of_range("Incorrect matrix");
    double res = 0;
    if (_rows == 1) {
        res = matrix[0][0];
    } else {
        for (int i = 0; i < _cols; i++) {
            S21Matrix M(minor_matrix(0, i));
            res += pow(-1, i) * matrix[0][i] * M.determinant();
            M.delete_matrix();
        }
    }
    return res;
}

S21Matrix S21Matrix::minor_matrix(int k, int l) {
    S21Matrix M(_rows - 1, _cols - 1);
    int q = 0;
    for (int i = 0; i < M._rows; i++) {
        int w = 0;
        if (q == k) q++;
        for (int j = 0; j < M._cols; j++) {
            if (w == l) w++;
            M.matrix[i][j] = matrix[q][w];
            w++;
        }
        q++;
    }
    return M;
}

S21Matrix S21Matrix::inverse_matrix() {
    double determ = determinant();
    if (determ == 0) {
        throw std::invalid_argument("Incorrect input: matrix determinant is 0");
    }
    S21Matrix res;
    if (_rows == 1) {
        res = S21Matrix(1, 1);
        res.matrix[0][0] = 1 / matrix[0][0];
    } else {
        res = S21Matrix(_rows, _cols);
        S21Matrix transpose(this->transpose());
        S21Matrix compll(transpose.calc_complements());
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                res.matrix[i][j] = compll.matrix[i][j] / determ;
            }
        }
    }
    return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) {
    S21Matrix res(o);
    res.sum_matrix(*this);
    return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) {
    S21Matrix res(*this);
    res.sub_matrix(o);
    return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) {
    S21Matrix res(*this);
    res.mul_matrix(o);
    return res;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix res(*this);
    res.mul_number(num);
    return res;
}

S21Matrix operator*(const double num, const S21Matrix& o) {
    S21Matrix res(o);
    res.mul_number(num);
    return res;
}

bool S21Matrix::operator==(const S21Matrix& o) {
    bool res = eq_matrix(o);
    return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
    if (this != &o) {
    recreate_matrix(o._rows, o._cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            matrix[i][j] = o.matrix[i][j];
        }
    }
    }
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
    sum_matrix(o);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
    sub_matrix(o);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
    mul_matrix(o);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
    mul_number(num);
    return *this;
}

double& S21Matrix::operator()(int row, int col) {
    if (row >= _rows || row < 0 || col >= _cols || col < 0)
        throw std::out_of_range("Incorrect input, index is out of range");
    return matrix[row][col];
}

double& S21Matrix::operator()(int row, int col) const {
    if (row >= _rows || row < 0 || col >= _cols || col < 0)
        throw std::out_of_range("Incorrect input, index is out of range");
    return matrix[row][col];
}

int S21Matrix::get_rows() const {
    return _rows;
}

int S21Matrix::get_cols() const {
    return _cols;
}

void S21Matrix::set_rows(int rows) {
    if (rows <= 0)
        throw std::out_of_range("Incorrect input, rows must be > 0");
    S21Matrix old_matrix(*this);
    recreate_matrix(rows, _cols);
    int min_rows = old_matrix._rows < _rows ? old_matrix._rows : _rows;
    for (int i = 0; i < min_rows; i++) {
        for (int j = 0; j < _cols; j++) {
            matrix[i][j] = old_matrix.matrix[i][j];
        }
    }
}

void S21Matrix::set_cols(int cols) {
    if (cols <= 0)
        throw std::out_of_range("Incorrect input, cols must be > 0");
    S21Matrix old_matrix(*this);
    recreate_matrix(_rows, cols);
    int min_cols = old_matrix._cols < _cols ? old_matrix._cols : _cols;
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < min_cols; j++) {
            matrix[i][j] = old_matrix.matrix[i][j];
        }
    }
}

void S21Matrix::recreate_matrix(int rows, int cols) {
    delete_matrix();
    _rows = rows;
    _cols = cols;
    matrix = new double*[_rows]();
    for (int i = 0; i < _rows; i++) {
        matrix[i] = new double[_cols]();
        for (int j = 0; j < _cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

void S21Matrix::delete_matrix() {
    if (matrix) {
        int i = 0;
        while (i < _rows && matrix[i]) {
            delete[] matrix[i];
            matrix[i] = NULL;
            i++;
        }
        delete[] matrix;
        matrix = NULL;
    }
    _rows = 0;
    _cols = 0;
}
