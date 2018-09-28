/*
 * Iluminacao.h
 *
 *  Created on: 26 de set de 2018
 *      Author: joao
 */

#ifndef ILUMINACAO_H_
#define ILUMINACAO_H_
#include "LightSource.h"
#include "Vector3.h"
#include "Texture.h"
using namespace std;
class Iluminacao {
public:
	Vector3 Ipix={0,0,0};
	Iluminacao(Vector3 observer , Vector3 Point_Object , Vector3 Normal_Of_Face , Texture Texture_Object , Light_Source sun , Light_Source post);
	Vector3 Generate_R_Vector(Vector3 l,Vector3 n);
	//Vector3 Genetate_N_Vector(Vector3 Point_Object);
	Vector3 Generate_L_Vector(Vector3 Point_Object, Light_Source post);
	Vector3 Generate_V_Vector(Vector3 Point_Object, Vector3 observer);
	Vector3 Idif(Light_Source post , Vector3 Texture_Object , Vector3 l , Vector3 n);
	Vector3 Iesp(Light_Source post , Vector3 Texture_Object , Vector3 r , Vector3 v ,int m);
};

#endif /* ILUMINACAO_H_ */
