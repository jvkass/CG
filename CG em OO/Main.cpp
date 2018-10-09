/*
 * Main.cpp
 *
 *  Created on: 21 de set de 2018
 *      Author: joao
 */
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

# include <GL/freeglut.h>


using namespace std;


#define RADIANOS_PARA_GRAUS 180 / 3.14159265358979323846f
#define GRAUS_PARA_RADIANOS 3.14159265358979323846f / 180

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Mesh.h"
#include "Transform.h"
#include "GameObject.h"
#include "LightSource.h"
#include "Iluminacao.h"
#include "Sphere.h"

GLdouble windowWidth  = 600.0;
GLdouble windowHeight = 600.0;

int window;



GameObject objeto[20];
int tamanho_vetor=1;

GLuint* vao;
GLuint* vbo;
GLuint* ibo;



//funcao que detecta se um raio passa por um triangulo
bool RayIntersectsTriangle(Vector3 rayOrigin, Vector3 rayVector, Vector3 vertex0, Vector3 vertex1, Vector3 vertex2 , Vector3 &aux , Vector3 N)
{
    float EPSILON = 0.0000001;

    Vector3 edge1(0,0,0);
    Vector3 edge2(0,0,0);
    Vector3 h(0,0,0);
    Vector3 s(0,0,0);
    Vector3 q(0,0,0);
    float a,f,u,v;

    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = rayVector.Cross(edge2);
    a = edge1.Dot(h);

    if (a > -EPSILON && a < EPSILON)
	{
        return false;
	}

    f = 1/a;
    s = rayOrigin - vertex0;
    u = f * (s.Dot(h));

    if (u < 0.0 || u > 1.0)
	{
        return false;
	}

    q = s.Cross(edge1);
    v = f * rayVector.Dot(q);

    if (v < 0.0 || u + v > 1.0)
	{
        return false;
	}

    if (f * edge2.Dot(q) > EPSILON)
    {	
    	
       //colocando valores teste para o calculo da cor, esses valores devem ser alterados
        Texture madeira=Texture({0.3f,0.3f,0.9f} , {0.3f,0.6f,0.9f} , {0.3f,0.6f,0.9f});
        
        Light_Source sun=Light_Source({0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f});
        Light_Source post=Light_Source({100.0f,100.0f,100.0f},{1.0f,1.0f,1.0f});
        //Vector3 N=Vector3(edge2[1]*edge1[1] - edge1[1] * edge2[2] , edge2[2] * edge1[0] - edge1[2]*edge2[0] , edge2[0]*edge1[1] - edge1[0]*edge2[1]);
       	
        Iluminacao rgb=Iluminacao({0.0f,0.0f,0.0f} , rayOrigin+rayVector*f*edge2.Dot(q) , N , madeira , sun , post);
       //observe a minha var aux recebendo a cor para depois eu usar no print
        aux=rgb.Ipix;
        return true;
    }
    else
	{
        return false;
	}
}



void Desenho(void)
{
	cout<<"Fazendo imagem"<<endl;
	// Teste com uma linha
	glClear(GL_COLOR_BUFFER_BIT);

//	glLoadIdentity();

//	glPointSize(3);


	glBegin(GL_POINTS);
	for(int i = 0; i < windowWidth; ++i){
		for(int j = 0; j < windowHeight; ++j){
			double x = (i  - windowWidth/2);
			double y = (j  - windowHeight/2);

			glColor3d(0.2,0.2,0.2);
			glVertex2d(x,y);
		}
	}
	Sphere barriga=Sphere({0.0f,-96.0f,300.0f}, 160.0f , Texture({0.5f,0.5f,0.5f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
	Sphere cabeca=Sphere({0.0f,150.0f,300.0f}, 100.0f , Texture({0.5f,0.5f,0.5f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
	Sphere olho_direito=Sphere({-50.0f,170.0f,300.0f}, 15.0f , Texture({0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f}));
	Sphere olho_esquerdo=Sphere({50.0f,170.0f,300.0f}, 15.0f , Texture({0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f}));
	Sphere nariz=Sphere({0.0f,130.0f,300.0f}, 15.0f , Texture({0.9f,0.2f,0.2f} , {0.9f,0.2f,0.2f} , {0.9f,0.2f,0.2f}));
	
	Sphere b1=Sphere({0.0f,0.0f,300.0f}, 15.0f , Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
	Sphere b2=Sphere({0.0f,-60.0f,300.0f}, 15.0f , Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
	Sphere b3=Sphere({0.0f,-120.0f,300.0f}, 15.0f , Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
	Sphere b4=Sphere({0.0f,-180.0f,300.0f}, 15.0f , Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
	





	Light_Source sun=Light_Source({0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f});
    Light_Source post=Light_Source({100.0f,100.0f,100.0f},{0.9f,0.9f,0.9f});
	for(int i = 0; i < windowWidth; ++i)
	{
		for(int j = 0; j < windowHeight; ++j)
		{
			double x = (i  - windowWidth/2);
			double y = (j - windowHeight/2);
			
			Vector3 aux=Vector3(1.0f,1.0f,1.0f);
					
					
			Vector3 observer={0.0f,0.0f,-130};
			Vector3 point={x,y,0};
			if(cabeca.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
				//cada cor sendo colocada no rgb							
    			glColor3d(aux[0],aux[1],aux[2]);

    			glVertex2d(x,y);
			}
			if(barriga.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
					
   				glColor3d(aux[0],aux[1],aux[2]);
    			glVertex2d(x,y);
			}

			if(olho_direito.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
					
   				glColor3d(aux[0],aux[1],aux[2]);
    			glVertex2d(x,y);
			}
			if(olho_esquerdo.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
					
   				glColor3d(aux[0],aux[1],aux[2]);
    			glVertex2d(x,y);
			}
			if(nariz.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
					
   				glColor3d(aux[0],aux[1],aux[2]);
    			glVertex2d(x,y);
			}
			if(b1.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
					
   				glColor3d(aux[0],aux[1],aux[2]);
    			glVertex2d(x,y);
			}
			if(b2.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
					
   				glColor3d(aux[0],aux[1],aux[2]);
    			glVertex2d(x,y);
			}
			if(b3.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
					
   				glColor3d(aux[0],aux[1],aux[2]);
    			glVertex2d(x,y);
			}if(b4.RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post)){
					
   				glColor3d(aux[0],aux[1],aux[2]);
    			glVertex2d(x,y);
			}
		}
	}
	cout<<"Fim"<<endl;
	glEnd();

	

	glFlush();
	
}


// Callback do GLUT: Chamado na criação da janela e toda vez que ela for redimensionada
void _Redimensionar(int w, int h)
{
	windowWidth = w;
	windowHeight = h;

	// Redefinição do viewport e projeção
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2, w/2, -h/2, h/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glutPostRedisplay();
}

// Callback do GLUT: Eventos de teclado
void _Teclado(unsigned char key, int x, int y)
{
	switch((char)key)
	{
		// ESC
		case 27:
			glutDestroyWindow(window);
			exit(0);
			break;
	}

	glutPostRedisplay();
}

// Callback do GLUT: Eventos de mouse com algum botão pressionado
void _Mouse(int x, int y)
{

}

int main(int argc, char *argv[])
{
	
	// Inicialização do GLUT e janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int) windowWidth, (int) windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)- windowWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)- windowHeight)/2);
	window = glutCreateWindow("O Melhor de Todos os Desenhos");

	glewExperimental = GL_TRUE;
	glewInit();


	// Definição de callbacks
	glutReshapeFunc(_Redimensionar);
	glutKeyboardFunc(_Teclado);
	glutMotionFunc(_Mouse);
	glutDisplayFunc(Desenho);


	glutMainLoop();
	exit(0);
}
