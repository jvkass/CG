#include "Sphere.h"

Sphere::Sphere(Vector3 centro , double raio){
	this->centro=centro;
	this->raio=raio;
}

bool Sphere::RayIntersects(Vector3 raydir,  Vector3 rayorig, Vector3 this->centro,float rad , Vector3 &aux)
{
float a = raydir.Dot(raydir);
float b = raydir .Dot( ( ( rayorig - this->centro)*2.0f));
float c = this->centro.Dot(this->centro) + rayorig.Dot(rayorig) -2.0f*rayorig.Dot(this->centro) - rad*rad;
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
        Vector3 normal=(hitpoint - this->centro) / rad;
		Texture madeira=Texture({0.3f,0.3f,0.9f} , {0.3f,0.6f,0.9f} , {0.3f,0.6f,0.9f});
        
        Light_Source sun=Light_Source({0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f});
        Light_Source this->centrot=Light_Source({100000.0f,1000000.0f,1000000.0f},{1.0f,1.0f,1.0f});
        Iluminacao rgb=Iluminacao({0.0f,0.0f,0.0f} , hitpoint , normal , madeira , sun , this->centrot);
       //observe a minha var aux recebendo a cor para depois eu usar no print
        aux=rgb.Ipix;   

        }
else
        return false;

return true;
}