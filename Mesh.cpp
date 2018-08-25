#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Mesh
{
	string nome;
	
	vector<Vector3> vertices;
	vector<Vector3> normaisVertices;
	vector<vector<vector<int>>> faces;
};


Mesh LoadObj(char* arquivo)
{
	Mesh mesh;
	
	string linha;
	Vector3 vec;
	
	ifstream obj(arquivo);
	
	if (obj.is_open())
	{
		while(getline(obj, linha))
		{
			if(linha[0] == '#' || linha.empty())
			{
				continue;
			}
			else if(linha[0] == 'g' || linha[0] == 'o')
			{
				mesh.nome = linha.substr(2);
			}
			else if(linha[0] == 'v' && linha[1] == 'n')
			{
				sscanf(linha.substr(3).c_str(), "%lf %lf %lf\n", vec[0], vec[1], vec[2]);
				
				mesh.normaisVertices.push_back(vec);
			}
			else if(linha[0] == 'v')
			{
				sscanf(linha.substr(3).c_str(), "%lf %lf %lf\n", vec[0], vec[1], vec[2]);
				
				mesh.vertices.push_back(vec);
			}
			else if(linha[0] == 'f')
			{
				vector<vector<int>> fac;
				fac.push_back({0, 0});
				fac.push_back({0, 0});
				fac.push_back({0, 0});
				
				sscanf(linha.substr(3).c_str(), "%i//%i %i//%i %i//%i\n", &fac[0][0], &fac[0][1], &fac[1][0], &fac[1][1], &fac[2][0], &fac[2][1]);
				
				mesh.faces.push_back({fac[0], fac[1], fac[2]});
			}
			
		}
		
		obj.close();
		
	}
	
	return mesh;
}