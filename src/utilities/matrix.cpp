// This file contains the definition of the class Matrix

#include "utilities/matrix.h"

// ----------------------------------------------------------------------- default constructor
// a default matrix is an identity matrix

Matrix::Matrix(void) {	
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m_[x][y] = 1.0;
			else
				m_[x][y] = 0.0;
		}
}


// ----------------------------------------------------------------------- copy constructor

Matrix::Matrix (const Matrix& mat) {
	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m_[x][y] = mat.m_[x][y];	
}


// ----------------------------------------------------------------------- destructor

Matrix::~Matrix (void) {}   


// ----------------------------------------------------------------------- assignment operator

Matrix& 
Matrix::operator= (const Matrix& rhs) {
	if (this == &rhs)
		return (*this);

	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m_[x][y] = rhs.m_[x][y];	

	return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication of two matrices

Matrix 
Matrix::operator* (const Matrix& mat) const {
	Matrix product;
	
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			double sum = 0.0;

			for (int j = 0; j < 4; j++)
				sum += m_[x][j] * mat.m_[j][y];
 
			product.m_[x][y] = sum;			
		}
	
	return (product);
}


// ----------------------------------------------------------------------- operator/
// division by a scalar

Matrix 
Matrix::operator/ (const double d) {
	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m_[x][y] = m_[x][y] / d;	

	return (*this);
}


// ----------------------------------------------------------------------- set_identity
// set matrix to the identity matrix

void											
Matrix::SetIdentity(void) {
    for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m_[x][y] = 1.0;
			else
				m_[x][y] = 0.0;
		}
}
