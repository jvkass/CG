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
#include "Texture.h"
#include "LightSource.h"
class Sphere: public GameObject {
public:
	Sphere(Vector3 centro , double raio , Texture textura);
	Vector3 centro={0,0,0};
	double raio;
	Texture textura=Texture({0,0,0},{0,0,0},{0,0,0});
	bool RayIntersects(Vector3 raydir,  Vector3 rayorig, Vector3 &aux , Vector3 observer , Light_Source sun , Light_Source post ,float &distance);
	
};

#endif /* SPHERE_H_ */
