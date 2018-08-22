/*
 * Main.cpp
 *
 *  Created on: 21 de ago de 2018
 *      Author: joao
 */
#include <iostream>
#include <string>
#include"Vector3.cpp"

using namespace std;


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

