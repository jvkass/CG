/*
 * Mesh.h
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#ifndef MESH_H_
#define MESH_H_
#include <string>
#include <vector>
#include "Vector3.h"
#include "Texture.h"
using namespace std;
class Mesh {
public:
	string nome;
	Texture textura=Texture({0,0,0},{0,0,0},{0,0,0});
	int tamanho_faces=0;
	vector<Vector3> vertices;
	vector<Vector3> normaisVertices;
	vector<vector<vector<unsigned short>>> faces;
	Mesh();
	int VerticesSize();
	int FacesSize();
};
void LoadObj(char* arquivo, Mesh* mesh);
#endif /* MESH_H_ */
