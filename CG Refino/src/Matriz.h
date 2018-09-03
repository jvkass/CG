/*
 * Matriz.h
 *
 *  Created on: 31 de ago de 2018
 *      Author: joao
 */

#ifndef MATRIZ_H_
#define MATRIZ_H_
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>

class Matriz {

private:
	double **M;
	int altura;
	int largura;
public:
	Matriz(int altura,int largura);
	std::string toString();
	double getValor(int altura,int largura);
	void setValor(int altura,int largura, double valor);
	bool validate(int altura,int largura);
	int getAltura();
	int getLargura();
	Matriz operator+(Matriz b);
	Matriz operator-(Matriz b);
	Matriz operator*(double b);
	Matriz operator*(Matriz b);
	Matriz operator/(double b);
	Matriz Translacao(double dx,double dy, double dz);
	Matriz Identidade(int altura);
	Matriz Escala(double Sx, double Sy, double Sz);
	Matriz ProdutoVetorial(double a1,double a2,double a3,double b1,double b2,double b3);
	Matriz Rotacao(double a1,double a2,double a3,double b1,double b2,double b3);
};

#endif /* MATRIZ_H_ */
