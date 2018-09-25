/*
 * Vector4.cpp
 *
 *  Created on: 25 de set de 2018
 *      Author: joao
 */

#define Vector4_UP		Vector4(0, 1, 0)
#define Vector4_DOWN	Vector4(0,-1, 0)
#define Vector4_LEFT	Vector4(-1, 0, 0)
#define Vector4_RIGHT	Vector4(1, 0, 0)
#define Vector4_FORWARD	Vector4(0, 0, 1)
#define Vector4_BACK	Vector4(0, 0, -1)
#define Vector4_ONE		Vector4(1, 1, 1)
#define Vector4_ZERO	Vector4(0, 0, 0)
#define RADIANOS_PARA_GRAUS 180 / 3.14159265358979323846f
#define GRAUS_PARA_RADIANOS 3.14159265358979323846f / 180



#include "Vector4.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

Vector4::Vector4() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 1;

}

Vector4::Vector4(double x_, double y_, double z_)
	{
		this->x = x_;
		this->y = y_;
		this->z = z_;
		this->w = 1;
}

double& Vector4::operator[](int id)
	{
		switch(id)
		{
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			case 3:
				return this->w;

		}
}

Vector4 Vector4::operator=(Vector4 v)
	{
		if(this != &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		return v;
}

Vector4 Vector4::operator+(Vector4 v)
	{
		return Vector4(x + v.x, y + v.y, z + v.z);
}

Vector4 Vector4::operator-(Vector4 v)
	{
		return Vector4(x - v.x, y - v.y, z - v.z);
}

Vector4 Vector4::operator*(double d)
	{
		return Vector4(x * d, y * d, z * d);
}

Vector4 Vector4::operator/(double d)
	{
		return Vector4(x / d, y / d, z / d);
}
bool Vector4::operator==(Vector4 v)
	{
		if((*this - v).MagnitudeSquared() < 9.99999944E-11f)
		{
			return true;
		}

		return false;
	}

	bool Vector4::operator!=(Vector4 v)
	{
		if((*this - v).MagnitudeSquared() < 9.99999944E-11f)
		{
			return false;
		}

		return true;
	}

	double Vector4::Magnitude()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	double Vector4::MagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z);
	}

	Vector4 Vector4::Normalize()
	{
		double mag = this->Magnitude();

		return Vector4(x / mag, y / mag, z / mag);
	}

	double Vector4::Dot(Vector4 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vector4 Vector4::Cross(Vector4 v)
	{
		return Vector4((y * v.z) - (z * v.y),
						(z * v.x) - (x * v.z),
						(x * v.y) - (y * v.x));
	}

	double Vector4::Angle(Vector4 v)
	{
		return acos(this->Dot(v) / (this->Magnitude() * v.Magnitude())) * RADIANOS_PARA_GRAUS;
	}

	Vector4 Vector4::Reflect(Vector4* plano)
	{

		Vector4 normal = (plano[1] - plano[0]).Cross(plano[2] - plano[0]).Normalize();
		return *this - normal * (2.0f * this->Dot(normal));

	}

	string Vector4::toString()
	{
		stringstream  s;
		s << "|" << x << "|" << y << "|" << z << "|" << w << "|";

		return s.str();
}

