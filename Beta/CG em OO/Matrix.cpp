/*
 * Matrix.cpp
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#include "Matrix.h"
#include "Vector4.h"
#include "Vector3.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#define RADIANOS_PARA_GRAUS 180 / 3.14159265358979323846f
#define GRAUS_PARA_RADIANOS 3.14159265358979323846f / 180
using namespace std;

Matrix::Matrix(int w, int h)
	{
		width = w;
		height = h;

		matrix = new double*[width];
		
		for (int i = 0; i < width; ++i)
		{
			matrix[i] = new double[height];
		}

		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				matrix[i][j] = 0;
			}
		}
	
}

double* Matrix::operator[](int id)
	{
		return matrix[id];
	}

Matrix Matrix::operator=(Matrix m)
	{
		Matrix ma(width, height);

		if(width != m.width || height != m.height)
		{
			return ma;
		}

		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				ma[i][j] = m[i][j];
			}
		}

		return ma;
	}

	Matrix Matrix::operator+(Matrix m)
	{
		if(width != m.width || height != m.height)
		{
			return Matrix(width, height);
		}

		Matrix ma(width, height);

		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				ma[i][j] = matrix[i][j] + m[i][j];
			}
		}

		return ma;
	}

	Matrix Matrix::operator-(Matrix m)
		{
			if(width != m.width || height != m.height)
			{
				return Matrix(width, height);
			}

			Matrix ma(width, height);

			for(int i = 0; i < width; ++i)
			{
				for(int j = 0; j < height; ++j)
				{
					ma[i][j] = matrix[i][j] - m[i][j];
				}
			}

			return ma;
		}

		Matrix Matrix::operator*(double d)
		{
			Matrix ma(width, height);

			for(int i = 0; i < width; ++i)
			{
				for(int j = 0; j < height; ++j)
				{
					ma[i][j] = matrix[i][j] * d;
				}
			}

			return ma;
		}

		Matrix Matrix::operator*(Matrix m)
		{
			if(height != m.width)
			{
				return Matrix(width, height);
			}

			Matrix ma(width, height);

			for(int i = 0; i < width; ++i)
			{
				for(int j = 0; j < height; ++j)
				{
					for(int k = 0; k < m.height; ++k)
					{
						ma[i][j] += matrix[i][k] * m[k][j];
					}
				}
			}

			return ma;
		}

		Vector3 Matrix::operator*(Vector3 v)
		{
			if(height != 4 || width != 4)
			{
				return Vector3(v.x, v.y, v.z);
			}

			Vector4 ve(v.x, v.y, v.z);



			//ve[i] = (v.x * matrix[i][0]) + (v.y * matrix[i][1]) + (v.z * matrix[i][2]);
			ve.x = (v.x * matrix[0][0]) + (v.y * matrix[0][1]) + (v.z * matrix[0][2]);
			ve.y = (v.x * matrix[1][0]) + (v.y * matrix[1][1]) + (v.z * matrix[1][2]);
			ve.z = (v.x * matrix[2][0]) + (v.y * matrix[2][1]) + (v.z * matrix[2][2]);
			ve.w = (v.x * matrix[3][0]) + (v.y * matrix[3][1]) + (v.z * matrix[3][2]);



			return Vector3(ve.x, ve.y, ve.z);
		}

		Vector4 Matrix::operator*(Vector4 v)
		{
			if(height != 4 || width != 4)
			{
				return Vector4(v.x, v.y, v.z);
			}

			Vector4 ve(v.x, v.y, v.z);

			ve.x = (v.x * matrix[0][0]) + (v.y * matrix[0][1]) + (v.z * matrix[0][2]);
			ve.y = (v.x * matrix[1][0]) + (v.y * matrix[1][1]) + (v.z * matrix[1][2]);
			ve.z = (v.x * matrix[2][0]) + (v.y * matrix[2][1]) + (v.z * matrix[2][2]);
			ve.w = (v.x * matrix[3][0]) + (v.y * matrix[3][1]) + (v.z * matrix[3][2]);

			return Vector4(ve.x, ve.y, ve.z);
		}

		Matrix Matrix::operator/(double d)
		{
			Matrix ma(width, height);

			for(int i = 0; i < width; ++i)
			{
				for(int j = 0; j < height; ++j)
				{
					ma[i][j] = matrix[i][j] / d;
				}
			}

			return ma;
		}

		Matrix Matrix::Transpose()
		{
			Matrix ma(height, width);

			for(int i = 0; i < height; ++i)
			{
				for(int j = 0; j < width; ++j)
				{
					ma[i][j] = matrix[j][i];
				}
			}

			return ma;
		}

		Vector3 Matrix::Translate(Vector3 v)
		{
			if(height != 4 || width != 4)
			{
				return v;
			}

			return Vector3(v.x + (matrix[0][3] * matrix[0][0]), v.y + (matrix[1][3] * matrix[1][1]), v.z + (matrix[2][3] * matrix[2][2]));
		}

		Vector4 Matrix::Translate(Vector4 v)
		{
			if(height != 4 || width != 4)
			{
				return v;
			}

			return Vector4(v.x + (matrix[0][3] * matrix[0][0]), v.y + (matrix[1][3] * matrix[1][1]), v.z + (matrix[2][3] * matrix[2][2]));
		}

		Vector3 Matrix::Scale(Vector3 v)
		{
			if(height != 4 || width != 4)
			{
				return v;
			}

			return Vector3(v.x * matrix[0][0], v.y * matrix[1][1], v.z * matrix[2][2]);
		}

		Vector4 Matrix::Scale(Vector4 v)
		{
			if(height != 4 || width != 4)
			{
				return v;
			}

			return Vector4(v.x * matrix[0][0], v.y * matrix[1][1], v.z * matrix[2][2]);
		}

		Vector3 Matrix::Rotate(Vector3 v, double angle, char axis)
		{
			if(height != 4 || width != 4)
			{
				return v;
			}

			angle = angle * GRAUS_PARA_RADIANOS;

			switch(axis)
			{
				case 'x':
					matrix[0][0] = 1;
					matrix[0][1] = 0;
					matrix[0][2] = 0;

					matrix[1][0] = 0;
					matrix[1][1] = cos(angle);
					matrix[1][2] = -sin(angle);

					matrix[2][0] = 0;
					matrix[2][1] = sin(angle);
					matrix[2][2] = cos(angle);
					break;
				case 'y':
					matrix[0][0] = cos(angle);
					matrix[0][1] = 0;
					matrix[0][2] = sin(angle);

					matrix[1][0] = 0;
					matrix[1][1] = 1;
					matrix[1][2] = 0;

					matrix[2][0] = -sin(angle);
					matrix[2][1] = 0;
					matrix[2][2] = cos(angle);
					break;
				case 'z':
					matrix[0][0] = cos(angle);
					matrix[0][1] = -sin(angle);
					matrix[0][2] = 0;

					matrix[1][0] = sin(angle);
					matrix[1][1] = cos(angle);
					matrix[1][2] = 0;

					matrix[2][0] = 0;
					matrix[2][1] = 0;
					matrix[2][2] = 1;
					break;
			}

			matrix[3][3] = 1;

			Vector3 ve = *this * v;

			return Vector3(ve.x, ve.y, ve.z);
		}

		string Matrix::toString()
		{
			stringstream  s;

			for(int i = 0; i < width; ++i)
			{
				for(int j = 0; j < height; ++j)
				{
					s << "|" << matrix[i][j] <<  "|";
				}

				s << "\n";
			}

			return s.str();
	}
