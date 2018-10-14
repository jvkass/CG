/*
 * Main.cpp
 *
 *  Created on: 21 de set de 2018
 *      Author: joao
 */

//includes do c++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>

//includes do GL
#include <GL/glew.h>
#include <GL/glut.h>
# include <GL/freeglut.h>

//arquivos usados
#include "Vector3.h"
#include "LightSource.h"
#include "Sphere.h"


using namespace std;

//dimensoes da tela
GLdouble windowWidth  = 600.0;
GLdouble windowHeight = 600.0;

int window;

GLuint* vao;
GLuint* vbo;
GLuint* ibo;


void Mundo_Camera(Vector3 camera , Vector3 LoockAt , Vector3 ViewUp , Vector3 &ponto){
	Vector3 Kc;
	Vector3 Ic;
	Vector3 Jc;
	Vector3 aux;

	Kc=(LoockAt-camera).Normalize();
	
	aux=ViewUp-LoockAt;

	Ic=(Kc.Cross(aux)).Normalize();

	Jc= (Ic.Cross(Kc)).Normalize();
	
	float MundoParaCamera[4][4];

	MundoParaCamera[0][0] = Ic[0];
	MundoParaCamera[0][1] = Ic[1];
	MundoParaCamera[0][2] = Ic[2];
	MundoParaCamera[0][3] = -Ic.Dot(camera);

	MundoParaCamera[1][0] = Jc[0];
	MundoParaCamera[1][1] = Jc[1];
	MundoParaCamera[1][2] = Jc[2];
	MundoParaCamera[1][3] = -Jc.Dot(camera);

	MundoParaCamera[2][0] = Kc[0];
	MundoParaCamera[2][1] = Kc[1];
	MundoParaCamera[2][2] = Kc[2];
	MundoParaCamera[2][3] = -Kc.Dot(camera);

	MundoParaCamera[3][0] = 0;
	MundoParaCamera[3][1] = 0;
	MundoParaCamera[3][2] = 0;
	MundoParaCamera[3][3] = 1;

	aux[0] = MundoParaCamera[0][0] * ponto[0] + MundoParaCamera[0][1] * ponto[1] + MundoParaCamera[0][2] * ponto[2] + MundoParaCamera[0][3];

	aux[1] = MundoParaCamera[1][0] * ponto[0] + MundoParaCamera[1][1] * ponto[1] + MundoParaCamera[1][2] * ponto[2] + MundoParaCamera[1][3];

	aux[2] = MundoParaCamera[2][0] * ponto[0] + MundoParaCamera[2][1] * ponto[1] + MundoParaCamera[2][2] * ponto[2] + MundoParaCamera[2][3];
	
	for (int i = 0; i < 3; i++){
 		ponto[i] = aux[i];
	}	

}

void Desenho(void)
{
	cout<<"Fazendo imagem"<<endl;
	// Teste com uma linha
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	//pintando o fundo
	for(int i = 0; i < windowWidth; ++i){
		for(int j = 0; j < windowHeight; ++j){
			double x = (i  - windowWidth/2);
			double y = (j  - windowHeight/2);

			glColor3d(0.2,0.2,0.5);
			glVertex2d(x,y);
		}
	}

	//definindo o boneco
	Sphere Snow_Man[9];

		Sphere barriga=Sphere({0.0f,-96.0f,300.0f}, 160.0f , Texture({0.5f,0.5f,0.5f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
	
		Sphere cabeca=Sphere({0.0f,150.0f,300.0f}, 100.0f , Texture({0.5f,0.5f,0.5f} , {0.3f,0.3f,0.3f} , {0.3f,0.3f,0.3f}));
	
		Sphere olho_direito=Sphere({-20.0f,100.0f,150.0f}, 8.0f , Texture({0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f}));
	
		Sphere olho_esquerdo=Sphere({20.0f,100.0f,150.0f}, 8.0f , Texture({0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f} , {0.2f,0.2f,0.2f}));
	
		Sphere nariz=Sphere({0.0f,80.0f,150.0f}, 8.0f , Texture({0.9f,0.2f,0.2f} , {0.9f,0.2f,0.2f} , {0.9f,0.2f,0.2f}));
	
		Sphere b1=Sphere({0.0f,0.0f,150.0f}, 8.0f , Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
		Sphere b2=Sphere({0.0f,-30.0f,150.0f}, 8.0f , Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
		Sphere b3=Sphere({0.0f,-50.0f,125.0f}, 6.5f , Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
		Sphere b4=Sphere({0.0f,-80.0f,125.0f}, 6.0f , Texture({0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f} , {0.2f,0.9f,0.2f}));
	
		Snow_Man[0]=cabeca;
		Snow_Man[1]=barriga;
		Snow_Man[2]=olho_direito;
		Snow_Man[3]=olho_esquerdo;
		Snow_Man[4]=nariz;
		Snow_Man[5]=b1;
		Snow_Man[6]=b2;
		Snow_Man[7]=b3;
		Snow_Man[8]=b4;

	//luzes	
	Light_Source sun=Light_Source({0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f});
    Light_Source post=Light_Source({100.0f,100.0f,100.0f},{0.9f,0.9f,0.9f});

	//onde esta a camera , para onde olha e a orientaçao
	Vector3 camera={0.0f,0.0f,-100};
	Vector3 LoockAt={0.0f,-96.0f,300.0f};
	Vector3 ViewUp= {0.0f,150.0f,300.0f};
	
	for(int k=0;k<9;k++){
		Mundo_Camera(camera,LoockAt,ViewUp,Snow_Man[k].centro);
			
	}

	Vector3 observer={0,0,0};
	for(int i = 0; i < windowWidth; ++i)
	{
		for(int j = 0; j < windowHeight; ++j)
		{
			//x e y
			double x = (i  - windowWidth/2);
			double y = (j - windowHeight/2);
			
			//inicializando vetor que armazena cor e a var que armazena a distancia
			//pos que limita o tamanho efetivo do vetor
			Vector3 aux=Vector3(1.0f,1.0f,1.0f);
			float t=-1.0f;
			int pos=0;

			//vetor que liga o observador a tela (x,y,d)		
			Vector3 point={x,y,150};

			//vetores que serao percorridos para achar seus menores valores
			float distancias[100];
			Vector3 cores[100];

			
			//percorrendo o boneco para tirar as medidas
			for(int k=0;k<9;k++){
				if(Snow_Man[k].RayIntersects(point - observer , {0.0f,0.0f,-1.0f} , aux , observer , sun , post , &t)){
					distancias[pos]=t;
					cores[pos]=aux;
					pos=pos+1;
				}
			}
			
			//laco para descobrir o menor t
			if(pos != 0){
				int menor=0;
				for(int k=0 ; k<pos ; k++){
					if(distancias[menor]>distancias[k]){
						menor=k;
					}
				}

				glColor3d(cores[menor][0],cores[menor][1],cores[menor][2]);
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
