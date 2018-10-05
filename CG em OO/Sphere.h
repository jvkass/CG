/*
 * Sphere.h
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#ifndef SPHERE_H_
#define SPHERE_H_
#include "Vector3.h"
#include "GameObject.h"
class Sphere: public GameObject {
public:
	Sphere(Vector3 centro , double raio);
	Vector3 centro={0,0,0};
	double raio;
	bool RayIntersects(Vector3 raydir,  Vector3 rayorig, Vector3 pos,float rad , Vector3 &aux)
	
};

#endif /* SPHERE_H_ */