/*
 * Matrix.h
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include <string>
using namespace std;
class Matrix {
public:
	/*atributos*/
	int rows;
	int columns;
	double **coordinates;

	/*construtores*/
	Matrix(int r, int c);
	Matrix(int r, int c, double **coords);

	/*operacoes*/

	double* operator[](int id);

	/*atribuicao*/
	Matrix operator=(Matrix& m);

	/*soma de matrizes*/
	Matrix operator+(Matrix& m);

	/*subtracao de matrizes*/
	Matrix operator-(Matrix& m);

	/*multiplicacao por um escalar*/
	Matrix operator*(double d);

	/*multiplicacao de matrizes*/
	Matrix operator*(Matrix m);

	/*divisao por um escalar*/
	Matrix  operator/(double d);

	/*igualdade e diferenca de matrizes*/
	bool    operator==(Matrix& v);
	bool    operator!=(Matrix& v);

	/*transposta*/
	Matrix transpose();

	/*visualizar*/
	string toString();


};

#endif /* MATRIX_H_ */
