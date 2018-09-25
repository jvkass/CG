#ifndef Mesh.h
#define Mesh.h


class Mesh{
public:
	string nome;
	
	vector<Vector3> vertices;
	vector<Vector3> normaisVertices;
	vector<vector<vector<unsigned short>>> faces;

	int VerticesSize(){}

	int FacesSize(){}

	void LoadObj(char* arquivo){}
};

#endif