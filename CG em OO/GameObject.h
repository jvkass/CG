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
#include "Texture.h"
class GameObject {
public:
	//GameObject();
	Mesh mesh;
	Transform transform;
	Texture texture = Texture(Vector3{0.6f,0.6f,0.9f} , Vector3{0.9f,0.9f,0.9f} , Vector3{0.9f,0.9f,0.9f});
};

#endif /* GAMEOBJECT_H_ */
