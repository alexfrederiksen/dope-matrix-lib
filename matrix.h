#pragma once

#include <iostream>
#include <iomanip> /* formatting */
#include <cstring> /* memcpy and memset */

template <typename T, int R, int C> class Matrix;

template <typename T, int R, int C>
std::ostream & operator <<(std::ostream & out, const Matrix<T, R, C> & mat);

template <typename T, int R, int C> class Matrix {
    public:
    /* fields */
    T m[R][C];

    /* constructors */
    Matrix();
    Matrix(T value);
    Matrix(T m[][C]);
    Matrix(const Matrix<T, R, C> & old);

    /* functions */
    Matrix<T, R, C> & set(T m[][C]);
    Matrix<T, R, C> & set(const Matrix<T, R, C> & mat);
    template <int c> Matrix<T, R, c> mul(const Matrix<T, C, c> & mat);
    Matrix<T, R, C> scl(const T scalar);
    Matrix<T, R, C> add(const Matrix<T, R, C> & mat);
    Matrix<T, C, R> transpose();
    Matrix<T, R, C> hadamard(const Matrix<T, R, C> & mat);
    template <typename F> Matrix<T, R, C> apply(F && func);
    template <typename F> Matrix<T, R, C> apply(F && func, const Matrix<T, R, C> & input);
    Matrix<T, R, C> & fill(const T value);
    Matrix<T, R, C> & fill(const Matrix<T, R, 1> & mat);
    Matrix<T, R, 1> col(const int c);
    Matrix<T, 1, C> row(const int r);

    /* operator overloads */
    template <int c> Matrix<T, R, c> operator *(const Matrix<T, C, c> & mat);
    Matrix<T, R, C> operator *(const T scalar);
    Matrix<T, R, C> operator /(const T scalar);
    Matrix<T, R, C> operator +(const Matrix<T, R, C> & mat);
    Matrix<T, R, C> operator -(const Matrix<T, R, C> & mat);
    void operator *=(const T scalar) { set(*this * scalar); }
    void operator /=(const T scalar) { set(*this / scalar); }
    void operator +=(const Matrix<T, R, C> & mat) { set(*this + mat); }
    void operator -=(const Matrix<T, R, C> & mat) { set(*this - mat); }
    
    template <typename F> Matrix<T, R, C> operator ()(F && func);
    template <typename F> Matrix<T, R, C> operator ()(F && func, const Matrix<T, R, C> & input);
    Matrix<T, R, C> & operator =(const Matrix<T, R, C> & mat);
    friend std::ostream & operator << <T, R, C>(std::ostream & out, const Matrix<T, R, C> & mat);

};

#include "matrix_impl.h"
