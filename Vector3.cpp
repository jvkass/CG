/*
 * Main.cpp
 *
 *  Created on: 22 de ago de 2018
 *      Author: glairton
 */
#include <iostream>
#include <string>

using namespace std;

class Vector3{

public:
	double vetor[3];
	
	Vector3()
	{
		vetor[0] = 0;
		vetor[1] = 0;
		vetor[2] = 0;
	}

	
	 Vector3(double x,double y,double z)
	 {
		vetor[0]=x;
		vetor[1]=y;
		vetor[2]=z;
	}

	double* operator[](int id)
	{
		return &vetor[id];
	}
	

	 virtual std::ostream& dump(std::ostream& o)const{
		 string resp;

		 return o<<"| "<<vetor[0]<<" |"<<"\n"
				 <<"| "<<vetor[1]<<" |"<<"\n"
				 <<"| "<<vetor[2]<<" |"<<"\n";
	 }



	 Vector3 Soma(Vector3 v){
		double X=this->vetor[0]+v.vetor[0];
		double Y=this->vetor[1]+v.vetor[1];
		double Z=this->vetor[2]+v.vetor[2];
		Vector3 resp(X,Y,Z);

		 return resp;
	 }

	 Vector3 Subtracao(Vector3 v){
		 double X=this->vetor[0]-v.vetor[0];
		 double Y=this->vetor[1]-v.vetor[1];
		 double Z=this->vetor[2]-v.vetor[2];

		 Vector3 resp(X,Y,Z);

		 return resp;
	 }

	 double ProdutoEscalar(Vector3 v){
		 double resp=vetor[0]*v.vetor[0] +
				  vetor[1]*v.vetor[1] +
			      vetor[2]*v.vetor[2];
		 	 return resp;
	 }


	 Vector3 ProdutoVetorial(Vector3 v){
		 double I=(vetor[1]*v.vetor[2]) - (vetor[2]*v.vetor[1]);
		 double J=(vetor[2]*v.vetor[0]) - (vetor[0]*v.vetor[2]);
		 double K=(vetor[0]*v.vetor[1]) - (vetor[1]*v.vetor[0]);

		 Vector3 resp(I,J,K);
		 return resp;
	 }


};
