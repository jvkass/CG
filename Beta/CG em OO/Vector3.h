/*
 * Vector3.h
 *
 *  Created on: 21 de set de 2018
 *      Author: joao
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_
#include <string>
using namespace std;
class Vector3 {
public:
	double x;
	double y;
	double z;
	double l;
	Vector3(double x, double y , double z);
	Vector3();
	double& operator[](int id);
	Vector3 operator=(Vector3 v);
	Vector3 operator+(Vector3 v);
	Vector3 operator-(Vector3 v);
	Vector3 operator*(double d);
	Vector3 operator/(double d);
	bool operator==(Vector3 v);
	bool operator!=(Vector3 v);
	Vector3 arroba(Vector3 v);
	double Magnitude();
	double MagnitudeSquared();
	Vector3 Normalize();
	double Dot(Vector3 v);
	Vector3 Cross(Vector3 v);
	double Angle(Vector3 v);
	Vector3 Reflect(Vector3* plano);
	string toString();

};

#endif /* VECTOR3_H_ */
