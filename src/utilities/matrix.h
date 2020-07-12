// this file contains the declaration of the class Matrix
// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix

#ifndef UTILITIES_MATRIX_H_
#define UTILITIES_MATRIX_H_

struct Matrix {
    double	m[4][4];
  
    Matrix();
    Matrix(const Matrix& mat);

    Matrix& operator= (const Matrix& rhs);
    Matrix operator* (const Matrix& mat) const;
    Matrix operator/ (const double d);

    void SetIdentity();	
};

#endif  // UTILITIES_MATRIX_H_
