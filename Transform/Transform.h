/*
 * Transform.h
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_
#include "Vector3.h"

class Transform {
public:
	Vector3 position={0,0,0};
	Vector3 rotation={0,0,0};
	Vector3 scale={1,1,1};
};

#endif /* TRANSFORM_H_ */
