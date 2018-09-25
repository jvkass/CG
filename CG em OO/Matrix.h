/*
 * Matrix.h
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include "Vector4.h"
#include "Vector3.h"
#include<string>
using namespace std;
class Matrix {
public:
	int width;
	int height;
	double** matrix;

	Matrix(int w, int h);
	double* operator[](int id);
	Matrix operator=(Matrix m);
	Matrix operator+(Matrix m);
	Matrix operator-(Matrix m);
	Matrix operator*(double d);
	Matrix operator*(Matrix m);
	Vector3 operator*(Vector3 v);
	Vector4 operator*(Vector4 v);
	Matrix operator/(double d);
	Matrix Transpose();
	Vector3 Translate(Vector3 v);
	Vector4 Translate(Vector4 v);
	Vector3 Scale(Vector3 v);
	Vector4 Scale(Vector4 v);
	Vector3 Rotate(Vector3 v, double angle, char axis);
	string toString();
};

#endif /* MATRIX_H_ */
