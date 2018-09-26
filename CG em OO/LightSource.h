/*
 * LightSource.h
 *
 *  Created on: 26 de set de 2018
 *      Author: joao
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_
#include "Vector3.h"
class Light_Source {
public://informacoes das fontes luminosas
	Light_Source(Vector3 position,Vector3 color);
	Vector3 position={0,0,0};
	Vector3 color={0,0,0};
};

#endif /* LIGHTSOURCE_H_ */
