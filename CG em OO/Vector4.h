/*
 * Vector4.h
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#ifndef VECTOR4_H_
#define VECTOR4_H_
#include<string>
using namespace std;
class Vector4 {
public:
	double x;
	double y;
	double z;
	double w;
	Vector4(double x_, double y_, double z_);
	Vector4();
	double& operator[](int id);
	Vector4 operator=(Vector4 v);
	Vector4 operator+(Vector4 v);
	Vector4 operator-(Vector4 v);
	Vector4 operator*(double d);
	Vector4 operator/(double d);
	bool operator==(Vector4 v);
	bool operator!=(Vector4 v);
	double Magnitude();
	double MagnitudeSquared();
	Vector4 Normalize();
	double Dot(Vector4 v);
	Vector4 Cross(Vector4 v);
	double Angle(Vector4 v);
	Vector4 Reflect(Vector4* plano);
	string toString();
};

#endif /* VECTOR4_H_ */
