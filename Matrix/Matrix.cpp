/*
 * Matrix.cpp
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#include "Matrix.h"
#include <string>
#include <sstream>
using namespace std;;
Matrix::Matrix(int r, int c)
{
	rows = r;
	columns = c;

	coordinates = new double*[rows];

	for (int i = 0; i < rows; ++i)
	{
		coordinates[i] = new double[columns];

		for (int j = 0; j < columns; ++j)
		{
			coordinates[i][j] = 0;
		}
	}
}

Matrix::Matrix(int r, int c, double **coords)
{
	rows = r;
	columns = c;

	coordinates = new double*[rows];

	for (int i = 0; i < rows; ++i)
	{
		coordinates[i] = new double[columns];

		for (int j = 0; j < columns; ++j)
		{
			coordinates[i][j] = coords[i][j];
		}
	}
}

double* Matrix::operator[](int id)
{
	return coordinates[id];
}

Matrix Matrix::operator=(Matrix& m)
{
	Matrix ma(rows, columns);

	if (rows != m.rows || columns != m.columns)
	{
		return ma;
	}

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			ma[i][j] = m[i][j];
		}
	}

	return ma;
}

Matrix Matrix::operator+(Matrix& m)
{
	if (rows != m.rows || columns != m.columns)
	{
		return Matrix(rows, columns);
	}

	Matrix ma(rows, columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			ma[i][j] = coordinates[i][j] + m[i][j];
		}
	}

	return ma;
}

Matrix Matrix::operator-(Matrix& m)
{
	if (rows != m.rows || columns != m.columns)
	{
		return Matrix(rows, columns);
	}

	Matrix ma(rows, columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			ma[i][j] = coordinates[i][j] - m[i][j];
		}
	}

	return ma;
}

Matrix Matrix::operator*(double d)
{
	Matrix ma(rows, columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			ma[i][j] = coordinates[i][j] * d;
		}
	}

	return ma;
}

Matrix Matrix::operator*(Matrix m)
{
	if (columns != m.rows)
	{
		return Matrix(rows, columns);
	}

	Matrix ma(rows, columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			for (int k = 0; k < m.columns; ++k)
			{
				ma[i][j] += coordinates[i][k] * m[k][j];
			}
		}
	}

	return ma;
}

Matrix Matrix::operator/(double d)
{
	Matrix ma(rows, columns);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			ma[i][j] = coordinates[i][j] / d;
		}
	}

	return ma;
}

Matrix Matrix::transpose()
{
	Matrix ma(columns, rows);

	for (int i = 0; i < columns; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			ma[i][j] = coordinates[j][i];
		}
	}

	return ma;
}

string Matrix::toString()
{
	stringstream  s;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			s << "[" << coordinates[i][j] << "]";
		}

		s << "\n";
	}

	return s.str();
}
