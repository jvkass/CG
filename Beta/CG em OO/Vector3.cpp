/*
 * Vector3.cpp
 *
 *  Created on: 21 de set de 2018
 *      Author: joao
 */
#define Vector3_UP		Vector3(0, 1, 0)
#define Vector3_DOWN	Vector3(0,-1, 0)
#define Vector3_LEFT	Vector3(-1, 0, 0)
#define Vector3_RIGHT	Vector3(1, 0, 0)
#define Vector3_FORWARD	Vector3(0, 0, 1)
#define Vector3_BACK	Vector3(0, 0, -1)
#define Vector3_ONE		Vector3(1, 1, 1)
#define Vector3_ZERO	Vector3(0, 0, 0)
#define RADIANOS_PARA_GRAUS 180 / 3.14159265358979323846f
#define GRAUS_PARA_RADIANOS 3.14159265358979323846f / 180


#include "Vector3.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
Vector3::Vector3(double x, double y, double z) {
	// TODO Auto-generated constructor stub
	this->x=x;
	this->y=y;
	this->z=z;

}

Vector3::Vector3(){
	this->x=0;
	this->y=0;
	this->z=0;
}

double& Vector3::operator [](int id){
	switch(id){
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
	}
}

Vector3 Vector3::operator=(Vector3 v){
	if(this != &v){
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
	return v;
}

Vector3 Vector3::operator+(Vector3 v){
	return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3 Vector3::operator-(Vector3 v){
	return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector3 Vector3::operator*(double d){
	return Vector3(this->x * d, this->y * d, this->z * d);
}

Vector3 Vector3::operator/(double d){
	return Vector3(this->x / d, this->y / d, this->z / d);
}
double Vector3::MagnitudeSquared()
	{
		return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
	}

bool Vector3::operator==(Vector3 v){
	if((*this - v).MagnitudeSquared() < 9.99999944E-11f){
				return true;
	}

	return false;
}
bool Vector3::operator!=(Vector3 v)
	{
		if((*this - v).MagnitudeSquared() < 9.99999944E-11f)
		{
			return false;
		}

		return true;
	}
Vector3 Vector3::arroba(Vector3 v){//multiplicacao um por um para calculo das cores
	return Vector3(this->x * v.x, this->y *v.y, this->z * v.z);
}
double Vector3::Magnitude()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

Vector3 Vector3::Normalize()
	{
		double mag = this->Magnitude();

		return Vector3(x / mag, y / mag, z / mag);
	}
double Vector3::Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

Vector3 Vector3::Cross(Vector3 v)
	{
		return Vector3((y * v.z) - (z * v.y),
						(z * v.x) - (x * v.z),
						(x * v.y) - (y * v.x));
	}
double Vector3::Angle(Vector3 v)
	{
		return acos(this->Dot(v) / (this->Magnitude() * v.Magnitude())) * RADIANOS_PARA_GRAUS;
	}
Vector3 Vector3::Reflect(Vector3* plano)
	{

	Vector3 normal = (plano[1] - plano[0]).Cross(plano[2] - plano[0]).Normalize();

	return *this - normal * (2.0f * this->Dot(normal));

	}
string Vector3::toString()
	{
		stringstream  s;
		s << "|" << x << "|" << y << "|" << z << "|\n";

		return s.str();
	}
