/*
 * Iluminacao.cpp
 *
 *  Created on: 26 de set de 2018
 *      Author: joao
 */

#include "Iluminacao.h"
#include "LightSource.h"
#include "Texture.h"
#include <math.h>
using namespace std;//adicionar as texturas do objeto
Iluminacao::Iluminacao(Vector3 observer , Vector3 Point_Object , Vector3 Normal_Of_Face , Texture Texture_Object , Light_Source sun , Light_Source post) {
	
	Vector3 n=Normal_Of_Face.Normalize();

	Vector3 l=Generate_L_Vector(Point_Object,post);
	Vector3 v=Generate_V_Vector(Point_Object, observer);
	Vector3 r=Generate_R_Vector(l,n);
	Ipix= sun.color.arroba(Texture_Object.texture_amb) + Idif(post , Texture_Object.texture_dif , l ,n) + Iesp(post , Texture_Object.texture_esp , r ,v,50);
}

Vector3 Iluminacao::Generate_L_Vector(Vector3 Point_Object, Light_Source post){
	return (post.position - Point_Object).Normalize();
}

Vector3 Iluminacao::Generate_V_Vector(Vector3 Point_Object, Vector3 observer){
	return (observer - Point_Object).Normalize();
}
Vector3 Iluminacao::Generate_R_Vector(Vector3 l,Vector3 n){
	return n*2*(l.Dot(n))- l;
}
Vector3 Iluminacao::Idif(Light_Source post , Vector3 Texture_Object , Vector3 l , Vector3 n){
	double cos=l.Dot(n);
	if(cos>=0){
		return post.color.arroba(Texture_Object) * cos;
	}else{
		return Vector3(0,0,0);
	}
}

Vector3 Iluminacao::Iesp(Light_Source post , Vector3 Texture_Object , Vector3 r , Vector3 v, int m){
	double cos=r.Dot(v);
	if(cos>=0){
		return post.color.arroba(Texture_Object) * pow(cos,m);
	}else{
		return Vector3(0,0,0);
	}
}


