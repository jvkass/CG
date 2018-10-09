/*
 * Mesh.cpp
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#include "Mesh.h"
#include "Vector3.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
using namespace std;
Mesh::Mesh() {
	// TODO Auto-generated constructor stub

}

int Mesh::VerticesSize(){
	return vertices.size() * 3 * sizeof(double);
}

int Mesh::FacesSize()
	{
		return faces.size() * faces[0].size() * faces[0][0].size() * sizeof(unsigned short);
}

void LoadObj(char* arquivo, Mesh* mesh)
{

	string linha;
	string linhaProcessada;

	Vector3 vec(0,0,0);
	vector<vector<unsigned short>> fac;
	fac.push_back({0, 0});
	fac.push_back({0, 0});
	fac.push_back({0, 0});

	ifstream obj(arquivo);

	if (obj.is_open())
	{
		while(getline(obj, linha))
		{
			if(linha[0] == '#' || linha.empty())
			{
				continue;
			}


			if(linha.size() >= 2)
			{
				linhaProcessada = linha.substr(2);
			}

			while(linhaProcessada[0] == ' ')
			{
				linhaProcessada = linhaProcessada.substr(1);
			}


			if(linha[0] == 'g' || linha[0] == 'o')
			{
				mesh->nome = linhaProcessada;
			}
			else if(linha[0] == 'v' && linha[1] == 'n')
			{
				sscanf(linhaProcessada.c_str(), "%lf %lf %lf\n", &vec.x, &vec.y, &vec.z);

				mesh->normaisVertices.push_back(vec);
			}
			else if(linha[0] == 'v')
			{
				sscanf(linhaProcessada.c_str(), "%lf %lf %lf\n", &vec.x, &vec.y, &vec.z);

				mesh->vertices.push_back(vec);
			}
			else if(linha[0] == 'f')
			{
				sscanf(linhaProcessada.c_str(), "%hi//%hi %hi//%hi %hi//%hi\n", &fac[0][0], &fac[0][1], &fac[1][0], &fac[1][1], &fac[2][0], &fac[2][1]);

				mesh->faces.push_back({fac[0], fac[1], fac[2]});
				mesh->tamanho_faces=1+mesh->tamanho_faces;
			}

		}

		obj.close();

	}
}
