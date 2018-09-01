/*
 * Matriz.cpp
 *
 *  Created on: 31 de ago de 2018
 *      Author: joao
 */

#include "Matriz.h"
#include <sstream>
#include <string>
Matriz::Matriz(int altura,int largura) {
	// TODO Auto-generated constructor stub
	this->altura=altura;
	this->largura=largura;
	M=(double**)malloc(sizeof (double*)*altura);
	for(int i=0;i<altura;i++){
		M[i]=(double*)malloc(sizeof (double)*largura);

	}

}
std::string Matriz::toString(){
	std::stringstream ss;

			for(int i = 0; i < altura; ++i)
			{

				ss<<"| ";
				for(int j = 0; j < largura; ++j)
				{
					if(j==largura-1){
						ss<<M[i][j]<<" |"<<"\n";
					}else{
					ss<< M[i][j] << " ";
					}
				}
			}
			return ss.str();
}

bool Matriz::validate(int altura,int largura){
	if(altura<0 or altura>this->altura){
			return false;
		}
		if(largura<0 or largura>this->largura){
				return false;
		}
		return true;
}

double Matriz::getValor(int altura,int largura){
	if(this->validate(altura,largura)){
		return M[altura][largura];
	}

	return -9999;
}

void Matriz::setValor(int altura,int largura, double valor){
	if(this->validate(altura,largura)){
		 M[altura][largura]=valor;
	}

}
int Matriz:: getLargura(){
	return largura;
}

int Matriz::getAltura(){
	return altura;
}
Matriz Matriz::operator +(Matriz b){
	if(altura != b.getAltura() or largura != b.getLargura()){
		return b;
	}
	Matriz resp(altura,largura);
	for(int i = 0; i < altura; ++i){

		for(int j = 0; j < largura; ++j){

			resp.setValor(i,j, this->getValor(i,j) + b.getValor(i,j));
		}
	}
	return resp;
}

Matriz Matriz:: operator -(Matriz b){
	if(altura != b.getAltura() or largura != b.getLargura()){
			return b;
		}
		Matriz resp(altura,largura);
		for(int i = 0; i < altura; ++i){

			for(int j = 0; j < largura; ++j){

				resp.setValor(i,j, this->getValor(i,j) - b.getValor(i,j));
			}
		}
		return resp;
}

Matriz Matriz:: operator *(double b){
	Matriz resp(altura,largura);
	for(int i=0;i<altura;i++){
		for(int j=0;j<largura;j++){
		resp.setValor(i,j, this->getValor(i,j) *b);
		}
	}
	return resp;
}

Matriz Matriz:: operator*(Matriz b){
	if(largura != b.getAltura()){
		return b;
	}

	Matriz resp(altura,b.getLargura());

	for(int i=0;i<altura;i++){

		for(int j=0;j<largura;j++){

			double Aux=0;

			for(int c=0;c<b.getLargura();c++){
				Aux=Aux+( M[i][c] * b.getValor(c,j) );

			}
			resp.setValor(i,j,Aux);
		}
	}

	return resp;

}

