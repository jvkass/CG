#include<string.h>
#include<iostream>
#include "Mesh.h"

class Mesh{
public:
	string nome;
	
	vector<Vector3> vertices;
	vector<Vector3> normaisVertices;
	vector<vector<vector<unsigned short>>> faces;

	Mesh();

	int VerticesSize(){
		return vertices.size() * 3 * sizeof(double);
	}

	int FacesSize(){
		return faces.size() * faces[0].size() * faces[0][0].size() * sizeof(unsigned short);
	}

	void LoadObj(char* arquivo){
		string linha;
		string linhaProcessada;

		Vector3 vec;
		vector<vector<unsigned short>> fac;
		fac.push_back({0, 0});
		fac.push_back({0, 0});
		fac.push_back({0, 0});

		ifstream obj(arquivo);

		if (obj.is_open()){
			
			while(getline(obj, linha)){
				
				if(linha[0] == '#' || linha.empty()){
					continue;
				}


				if(linha.size() >= 2){
					linhaProcessada = linha.substr(2);
				}

				while(linhaProcessada[0] == ' '){
					linhaProcessada = linhaProcessada.substr(1);
				}


				if(linha[0] == 'g' || linha[0] == 'o'){
					this->nome = linhaProcessada;
				}

				else if(linha[0] == 'v' && linha[1] == 'n'){
					sscanf(linhaProcessada.c_str(), "%lf %lf %lf\n", &vec[0], &vec[1], &vec[2]);

					this->normaisVertices.push_back(vec);
				}
				else if(linha[0] == 'v'){
					sscanf(linhaProcessada.c_str(), "%lf %lf %lf\n", &vec[0], &vec[1], &vec[2]);

					this->vertices.push_back(vec);
				}
				else if(linha[0] == 'f'){
					sscanf(linhaProcessada.c_str(), "%hi//%hi %hi//%hi %hi//%hi\n", &fac[0][0], &fac[0][1], &fac[1][0], &fac[1][1], &fac[2][0], &fac[2][1]);

					this->faces.push_back({fac[0], fac[1], fac[2]});
				}

			}

			obj.close();
		}	
	}


};