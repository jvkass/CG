/*
 * GameObject.h
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "Mesh.h"
#include "Transform.h"
#include "Vector3.h"
class GameObject {
public:
	//GameObject();
	Mesh mesh;
	Transform transform;
	Vector3 color={0,0,0};
};

#endif /* GAMEOBJECT_H_ */
