/*
 * Matriz.cpp
 *
 *  Created on: 31 de ago de 2018
 *      Author: joao
 */

#include "Matriz.h"
#include <sstream>
#include <string>
#include <iostream>
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

Matriz Matriz::operator/(double b){
	Matriz resp(altura,largura);
	for(int i=0;i<altura;i++){
		for(int j=0;j<largura;j++){
			resp.setValor(i,j, this->getValor(i,j)/b);
		}
	}
	return resp;
}
Matriz Matriz::Identidade(int altura){
	Matriz I(altura,altura);
	for(int i=0;i<altura;i++){
		I.setValor(i,i,1);
	}
	return I;
}

Matriz Matriz::Translacao(double dx,double dy,double dz){//retorna a matriz de translacao
	Matriz Translacao(altura,largura);
	Translacao=Translacao.Identidade(4);
	Translacao.setValor(0,3,dx);
	Translacao.setValor(1,3,dy);
	Translacao.setValor(2,3,dz);
	return Translacao;

}

Matriz Matriz::Escala(double Sx, double Sy, double Sz){
	Matriz Escala(4,4);
	Escala.setValor(0,0,Sx);
	Escala.setValor(1,1,Sy);
	Escala.setValor(2,2,Sz);
	return Escala;
}
Matriz Matriz::ProdutoVetorial(double a1,double a2,double a3,double b1,double b2,double b3){
		 double I=(a2*b3) - (a3*b2);
		 double J=(a3*b1) - (a1*b3);
		 double K=(a1*b2) - (a2*b1);

		 Matriz resp(4,1);

		 resp.setValor(0,0,I);
		 resp.setValor(0,1,J);
		 resp.setValor(0,2,K);
		 resp.setValor(0,3,1);

		 return resp;
	 }
	double raiz(double numero){
		double precisao=0.000001;
		double b =numero, a=1;

		while((b-a)>= precisao){
			b=(a+b)/2;
			a=numero/b;
		}
		return b;
	}
Matriz Matriz::Rotacao(double a1,double a2,double a3,double b1,double b2,double b3){
	Matriz p1(3,1);

	p1.setValor(0,0,a1);
	p1.setValor(0,1,a2);
	p1.setValor(0,2,a3);
	//p1.setValor(0,3,1);

	Matriz p2(3,1);

	p2.setValor(0,0,b1);
	p2.setValor(0,1,b2);
	p2.setValor(0,2,b3);
	//p1.setValor(0,3,1);

	Matriz I(3,1);

	I.setValor(0,0, b1 - a1);
	I.setValor(0,1,b2 - a2);
	I.setValor(0,2,b3 - a3);

	Matriz p3(3,1);//ponto auxiliar

	p3.setValor(0,0,a1);
	p3.setValor(0,1,a2);
	p3.setValor(0,2,raiz(a3+b3));

	Matriz K(3,1);

	K.setValor(0,0, a1-a1);
	K.setValor(0,1,a2-a2);
	K.setValor(0,2,p3.getValor(0,2)-a3);

	Matriz J = I.ProdutoVetorial( I.getValor(0,0) , I.getValor(0,1) , I.getValor(0,2),
			K.getValor(0,0) , K.getValor(0,1) , K.getValor(0,2) );

	K=I.ProdutoVetorial( I.getValor(0,0) , I.getValor(0,1) , I.getValor(0,2),
			J.getValor(0,0) , J.getValor(0,1) , J.getValor(0,2) );

	double NormaI=raiz(I.getValor(0,0) + I.getValor(0,1) + I.getValor(0,2));
	double NormaJ=raiz(J.getValor(0,0) + J.getValor(0,1) + J.getValor(0,2));
	double NormaK=raiz(K.getValor(0,0) + K.getValor(0,1) + K.getValor(0,2));

	Matriz i=I/NormaI;
	Matriz j=J/NormaJ;
	Matriz k=K/NormaK;







}
