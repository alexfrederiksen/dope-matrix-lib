#include "matrix.h"

template <typename T, int R, int C>
Matrix<T, R, C>::Matrix() {
    //std::cout << "Default constructor called.\n";
    fill(0);
}

template <typename T, int R, int C> 
Matrix<T, R, C>::Matrix(T value) {
    fill(value);
}

template <typename T, int R, int C>
Matrix<T, R, C>::Matrix(T m[][C]) {
    set(m);
}

template <typename T, int R, int C>
Matrix<T, R, C>::Matrix(const Matrix<T, R, C> & old) {
    //std::cout << "Copy constructor called.\n";
    set(old);
}

template <typename T, int R, int C>
Matrix<T, R, C> & Matrix<T, R, C>::set(const Matrix<T, R, C> & mat) {
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            m[r][c] = mat.m[r][c];
        }
    }
    //std::cout << "Copied from other matrix.\n";
    return *this;
}

template <typename T, int R, int C>
Matrix<T, R, C> & Matrix<T, R, C>::set(T _m[][C]) {
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            m[r][c] = _m[r][c];
        }
    }
    return *this;
}

template <typename T, int R, int C> 
template <int c> 
Matrix<T, R, c> Matrix<T, R, C>::mul(const Matrix<T, C, c> & mat) {
    Matrix<T, R, c> out;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < C; k++) {
                out.m[i][j] += m[i][k] * mat.m[k][j];
            }
        }
    }
    return out;
}

template <typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::scl(const T scalar) {
    return apply([scalar](T in) { return in * scalar; });
}

template <typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::add(const Matrix<T, R, C> & mat) {
    return apply([](float x, float y) { x + y; }, mat);
}

template <typename T, int R, int C>
Matrix<T, C, R> Matrix<T, R, C>::transpose() {
    Matrix<T, C, R> out;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            out.m[j][i] = m[i][j];
        }
    }
    return out;
}

template <typename T, int R, int C>
Matrix<T, R, C>  Matrix<T, R, C>::hadamard(const Matrix<T, R, C> & mat) {
    Matrix<T, R, C> out;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            out.m[i][j] = m[i][j] * mat.m[i][j];
        }
    }
    return out;
}

template <typename T, int R, int C>
template <typename F>
Matrix<T, R, C> Matrix<T, R, C>::apply(F && func) {
    Matrix<T, R, C> out;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            out.m[i][j] = func(m[i][j]);
        }
    }
    return out;
}

template <typename T, int R, int C>
template <typename F> 
Matrix<T, R, C> Matrix<T, R, C>::apply(F && func, const Matrix<T, R, C> & input) {
    Matrix<T, R, C> out;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            out.m[i][j] = func(m[i][j], input.m[i][j]);
        }
    }
    return out;
}

template <typename T, int R, int C>
Matrix<T, R, C> & Matrix<T, R, C>::fill(const T value) {
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            m[r][c] = value;
        }
    }
    return *this;
}

template <typename T, int R, int C>
Matrix<T, R, C> & Matrix<T, R, C>::fill(const Matrix<T, R, 1> & mat) {
    for (int c = 0; c < C; c++) {
        for (int r = 0; r < R; r++) {
            m[r][c] = mat.m[r][0];   
        }
    }
    return *this;
}

template <typename T, int R, int C>
Matrix<T, R, 1> Matrix<T, R, C>::col(const int c) {
    if (c < 0 || c >= C) {
        std::cerr << "Matrix::col(): Invalid column selection.\n";
    }
    Matrix<T, R, 1> mat;
    for (int r = 0; r < R; r++) {
        mat.m[r][0] = m[r][c];
    }
    return mat;
}

template <typename T, int R, int C>
Matrix<T, 1, C> Matrix<T, R, C>::row(const int r) {
    if (r < 0 || r >= R) {
        std::cerr << "Matrix::row(): Invalid row selection.\n";
    }
    Matrix<T, 1, C> mat;
    for (int c = 0; c < C; c++) {
        mat.m[0][c] = mat.m[r][c];
    }
    return mat;
}

/* operators */


template <typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::operator *(const T scalar) {
    return scl(scalar);
}

template <typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::operator /(const T scalar) {
    return scl(1.0 / scalar);
}

template <typename T, int R, int C>
template <int c> 
Matrix<T, R, c> Matrix<T, R, C>::operator *(const Matrix<T, C, c> & right) {
    return mul(right);
}

template <typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::operator +(const Matrix<T, R, C> & mat) {
    return apply([](float x, float y) { return x + y; }, mat);
}

template <typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::operator -(const Matrix<T, R, C> & mat) {
    return apply([](float x, float y) { return x - y; }, mat);
}

template <typename T, int R, int C>
template <typename F>
Matrix<T, R, C> Matrix<T, R, C>::operator ()(F && func) {
    return apply(func);
}

template <typename T, int R, int C>
template <typename F>
Matrix<T, R, C> Matrix<T, R, C>::operator ()(F && func, const Matrix<T, R, C> & input) {
    return apply(func, input);
}


template <typename T, int R, int C>
Matrix<T, R, C> & Matrix<T, R, C>::operator =(const Matrix<T, R, C> & mat) {
    set(mat);
    return *this;
}

template <typename T, int R, int C>
std::ostream & operator <<(std::ostream & out, const Matrix<T, R, C> & mat) {
    out << "MAT {";
    for (int i = 0; i < R; i++) {
        if (i > 0) out << "    {";
        for (int j = 0; j < C; j++) {
            out << " " << std::setw(8) << std::setprecision(3) 
                << std::fixed << mat.m[i][j];
        }
        out << " }" << std::endl;
    }
    return out;
}
