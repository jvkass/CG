#ifndef PLANO_H_
#define PLANO_H_

#include "Vector3.h"
#include "Texture.h"

using namespace std;
class Plano {
public:
	Vector3 v1=Vector3(0,0,0);
	Vector3 v2=Vector3(0,0,0);
	Vector3 v3=Vector3(0,0,0);
	Vector3 v4=Vector3(0,0,0);

	Texture textura=Texture({0,0,0},{0,0,0},{0,0,0});
	
	Plano(Texture textura, Vector3 v1 , Vector3 v2 , Vector3 v3 , Vector3 v4);
	Plano();
	
	bool RayIntersects(Vector3 raydir,  Vector3 rayorig, Vector3 &aux , Vector3 observer , Light_Source sun , Light_Source post ,float *distance);
	bool RayIntersectsTriangle(Vector3 rayOrigin, Vector3 rayVector, Vector3 vertex0, Vector3 vertex1, Vector3 vertex2 , Vector3 &aux , Vector3 N);
};

#endif /* PLANO_H_ */