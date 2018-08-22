/*
 * Main.cpp
 *
 *  Created on: 21 de ago de 2018
 *      Author: joao
 */
#include <iostream>
#include <string>

using namespace std;

class Vector3{//nome da classe

public://parte do codigo onde ficam as variaveis e metodos publicos
	int vetor[3];
	 Vector3(int x,int y,int z){//construtor
		vetor[0]=x;
		vetor[1]=y;
		vetor[2]=z;
	}


	 virtual std::ostream& dump(std::ostream& o)const{//metodo toString para printar a classe mais naturalmente
		 string resp;

		 return o<<"| "<<vetor[0]<<" |"<<"\n"
				 <<"| "<<vetor[1]<<" |"<<"\n"
				 <<"| "<<vetor[2]<<" |"<<"\n";
	 }



	 Vector3 Soma(Vector3 v){
		int X=this->vetor[0]+v.vetor[0];
		int Y=this->vetor[1]+v.vetor[1];
		int Z=this->vetor[2]+v.vetor[2];
		Vector3 resp(X,Y,Z);

		 return resp;
	 }

	 Vector3 Subtracao(Vector3 v){
		 int X=this->vetor[0]-v.vetor[0];
		 int Y=this->vetor[1]-v.vetor[1];
		 int Z=this->vetor[2]-v.vetor[2];

		 Vector3 resp(X,Y,Z);

		 return resp;
	 }

	 int ProdutoEscalar(Vector3 v){
		 int resp=vetor[0]*v.vetor[0] +
				  vetor[1]*v.vetor[1] +
			      vetor[2]*v.vetor[2];
		 	 return resp;
	 }


	 Vector3 ProdutoVetorial(Vector3 v){
		 int I=(vetor[1]*v.vetor[2]) - (vetor[2]*v.vetor[1]);
		 int J=(vetor[2]*v.vetor[0]) - (vetor[0]*v.vetor[2]);
		 int K=(vetor[0]*v.vetor[1]) - (vetor[1]*v.vetor[0]);

		 Vector3 resp(I,J,K);
		 return resp;
	 }


};

std::ostream& operator<<(std::ostream& o, Vector3 b){return b.dump(o);}
//continuaçao do toString
int main(){

	Vector3 teste(0,0,0);
	Vector3 teste2(10,1,1);
	teste=teste.Soma(teste2);
	cout<<teste<<endl;
	teste=teste.Subtracao(teste);
	cout<<teste<<endl;


	return 0;
}

