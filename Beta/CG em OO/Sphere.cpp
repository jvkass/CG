#include "Sphere.h"
#include <math.h>
#include "LightSource.h" 
#include "Iluminacao.h"
Sphere::Sphere(Vector3 centro , double raio , Texture textura){
	this->centro=centro;
	this->raio=raio;
	this->textura=textura;
}

bool Sphere::RayIntersects(Vector3 raydir,  Vector3 rayorig, Vector3 &aux , Vector3 observer , Light_Source sun , Light_Source post , float &distance)
{
float a = raydir.Dot(raydir);
float b = raydir .Dot( ( ( rayorig - this->centro)*2.0f));
float c = this->centro.Dot(this->centro) + rayorig.Dot(rayorig) -2.0f*rayorig.Dot(this->centro) - this->raio*this->raio;
float D = b*b + (-4.0f)*a*c;

// If ray can not intersect then stop
if (D < 0)
        return false;
D=sqrtf(D);

// Ray can intersect the sphere, solve the closer hitpoint
float t = (-0.5f)*(b+D)/a;
if (t > 0.0f)
        {
        float distance=sqrtf(a)*t;
        Vector3 hitpoint=rayorig + raydir*t;
        Vector3 normal=(hitpoint - this->centro) / this->raio;
		
       
        Iluminacao rgb=Iluminacao(observer , hitpoint , normal , this->textura , sun , post);
       
        aux=rgb.Ipix;   
        distance=t;

        }
else
        return false;

return true;
}