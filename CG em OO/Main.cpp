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

GLdouble windowWidth  = 800.0;
GLdouble windowHeight = 600.0;

int window;



GameObject objeto[20];
int tamanho_vetor=9;

GLuint* vao;
GLuint* vbo;
GLuint* ibo;


bool RayIntersectsSphere(Vector3 raydir,  Vector3 rayorig, Vector3 pos,float rad , Vector3 &aux)
{
float a = raydir.Dot(raydir);
float b = raydir .Dot( ( ( rayorig - pos)*2.0f));
float c = pos.Dot(pos) + rayorig.Dot(rayorig) -2.0f*rayorig.Dot(pos) - rad*rad;
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
        Vector3 normal=(hitpoint - pos) / rad;
		Texture madeira=Texture({0.3f,0.3f,0.9f} , {0.3f,0.6f,0.9f} , {0.3f,0.6f,0.9f});
        
        Light_Source sun=Light_Source({0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f});
        Light_Source post=Light_Source({100000.0f,1000000.0f,1000000.0f},{1.0f,1.0f,1.0f});
        Iluminacao rgb=Iluminacao({0.0f,0.0f,0.0f} , hitpoint , normal , madeira , sun , post);
       //observe a minha var aux recebendo a cor para depois eu usar no print
        aux=rgb.Ipix;   

        }
else
        return false;

return true;
}
//funcao que detecta se um raio passa por um triangulo
bool RayIntersectsTriangle(Vector3 rayOrigin, Vector3 rayVector, Vector3 vertex0, Vector3 vertex1, Vector3 vertex2 , Vector3 &aux , Vector3 N, Texture T, Vector3& out)
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
        
        Light_Source sun=Light_Source({10.0f,0.0f,0.0f},{1.0f,1.0f,1.0f});
        Light_Source post=Light_Source({100000.0f,1000000.0f,1000000.0f},{1.0f,1.0f,1.0f});
        //Vector3 N=Vector3(edge2[1]*edge1[1] - edge1[1] * edge2[2] , edge2[2] * edge1[0] - edge1[2]*edge2[0] , edge2[0]*edge1[1] - edge1[0]*edge2[1]);
       	
        Iluminacao rgb=Iluminacao({0.0f,0.0f,0.0f} , rayOrigin+rayVector*f*edge2.Dot(q) , N , T , sun , post);
       //observe a minha var aux recebendo a cor para depois eu usar no print
        aux=rgb.Ipix;
		
		out = rayOrigin + rayVector * f; 
        return true;
    }
    else
	{
        return false;
	}
}



void Desenho(void)
{
	// Teste com uma linha
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glPointSize(3);


	glBegin(GL_POINTS);
	for(int i = 0; i < windowWidth/3; ++i){
		for(int j = 0; j < windowHeight/3; ++j){
			double x = (i * 3 - windowWidth/2);
			double y = (j * 3 - windowHeight/2);

			glColor3d(0,0,0);
			glVertex2d(x,y);
		}
	}
	
	for(int k=0 ; k<tamanho_vetor ; k++){

		for(int f=0 ; f < objeto[k].mesh.tamanho_faces ; f++){

			if(objeto[k].mesh.normaisVertices[ objeto[k].mesh.faces[f][0][1] -1 ].z > 0)
			{
				continue;
			}

			for(int i = 0; i < windowWidth/3; ++i)
			{
				for(int j = 0; j < windowHeight/3; ++j)
				{
					double x = (i * 3 - windowWidth/2);
					double y = (j * 3 - windowHeight/2);
					
					
						Vector3 aux=Vector3(1.0f,1.0f,1.0f);
						Vector3 aux2=Vector3(0,0,0);
						
						
						
						Vector3 v1 = Vector3(objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][0][0] -1 ][0], objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][0][0] -1 ][1], objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][0][0] -1 ][2]);
						
						Vector3 v2 = Vector3(objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][1][0] -1 ][0], objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][1][0] -1 ][1], objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][1][0] -1 ][2]);
						
						Vector3 v3 = Vector3(objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][2][0] -1 ][0], objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][2][0] -1 ][1], objeto[k].mesh.vertices[ objeto[k].mesh.faces[f][2][0] -1 ][2]);
						Vector3 N = objeto[k].mesh.normaisVertices[ objeto[k].mesh.faces[f][0][1] -1  ];
						
						if(RayIntersectsTriangle({x,y,-1}, {x,y, 1},v1,v2,v3,aux,N, objeto[k].texture, aux2)){
						//cada cor sendo colocada no rgb
								
								glColor3d(aux[0],aux[1],aux[2]);

								glVertex3d(x,y, aux2.z);
							
							//glColor3d(aux[0],aux[1],aux[2]);
						}else{
					//cor de fundo
							

							//glColor3d(0,0,1);
						}
						//glVertex2d(x,y);
									

					

					//glColor3d(RayIntersectsTriangle({0,0,-1}, {x,y, 1}, {-100,-100,0}, {0,100,0}, {100,-100,0}),1,0.10f);

					//glVertex2d(x,y);
				}
			}

		//glVertex2d(x,y);
		}
	
	}
	


	glEnd();

	

	glutSwapBuffers();
	
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

	glutPostRedisplay();
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
	srand(time(NULL));



	// Inicialização do GLUT e janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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


	// Definição de cor de fundo,  cor de desenho e espessura da linha de teste
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);

	
	

	for(int i = 0; i < 20; ++i)
	{
		LoadObj("cube.obj", &objeto[i].mesh);
		
		switch(i)
		{
			case 0:
				objeto[i].transform.scale = Vector3{1, 1, 1};
				objeto[i].transform.position = Vector3{-100, -200, 0};
			break;
			case 1:
				objeto[i].transform.scale = Vector3{0.8, 0.8, 0.8};
				objeto[i].transform.position = Vector3{-80, 0, 0};
			break;
			case 2:
				objeto[i].transform.scale = Vector3{0.2, 0.2, 0.2};
				objeto[i].transform.position = Vector3{-20, -140, 0};
				objeto[i].texture = Texture(Vector3{0.2f,0.2f,0.2f} , Vector3{0.5f,0.5f,0.5f} , Vector3{0.5f,0.5f,0.5f});
			break;
			case 3:
				objeto[i].transform.scale = Vector3{0.2, 0.2, 0.2};
				objeto[i].transform.position = Vector3{-20, -80, 0};
				objeto[i].texture = Texture(Vector3{0.2f,0.2f,0.2f} , Vector3{0.5f,0.5f,0.5f} , Vector3{0.5f,0.5f,0.5f});
			break;
			case 4:
				objeto[i].transform.scale = Vector3{0.1, 0.1, 0.1};
				objeto[i].transform.position = Vector3{-40, 100, 0};
				objeto[i].texture = Texture(Vector3{0.2f,0.2f,0.2f} , Vector3{0.5f,0.5f,0.5f} , Vector3{0.5f,0.5f,0.5f});
			break;
			case 5:
				objeto[i].transform.scale = Vector3{0.1, 0.1, 0.1};
				objeto[i].transform.position = Vector3{40, 100, 0};
				objeto[i].texture = Texture(Vector3{0.2f,0.2f,0.2f} , Vector3{0.5f,0.5f,0.5f} , Vector3{0.5f,0.5f,0.5f});
			break;
			case 6:
				objeto[i].transform.scale = Vector3{0.1, 0.1, 0.1};
				objeto[i].transform.position = Vector3{-10, 60, 0};
				objeto[i].texture = Texture(Vector3{0.2f,0.2f,0.2f} , Vector3{0.5f,0.5f,0.5f} , Vector3{0.5f,0.5f,0.5f});
			break;
			case 7:
				objeto[i].transform.scale = Vector3{1, 0.1, 0.4};
				objeto[i].transform.position = Vector3{-100, 140, 0};
				objeto[i].texture = Texture(Vector3{0.3f,0.2f,0.1f} , Vector3{0.5f,0.4f,0.3f} , Vector3{0.5f,0.4f,0.3f});
			break;
			case 8:
				objeto[i].transform.scale = Vector3{0.8, 0.3, 0.4};
				objeto[i].transform.position = Vector3{-80, 150, 0};
				objeto[i].texture = Texture(Vector3{0.3f,0.2f,0.1f} , Vector3{0.5f,0.4f,0.3f} , Vector3{0.5f,0.4f,0.3f});
			break;
		}

		Matrix m2{4, 4};
		m2[0][0] = objeto[i].transform.scale.x;
		m2[1][1] = objeto[i].transform.scale.y;
		m2[2][2] = objeto[i].transform.scale.z;
		m2[3][3] = 1;

		Matrix m1{4, 4};
		m1[0][0] = 1;
		m1[1][1] = 1;
		m1[2][2] = 1;
		m1[3][3] = 1;
		m1[0][3] = objeto[i].transform.position.x;
		m1[1][3] = objeto[i].transform.position.y;
		m1[2][3] = objeto[i].transform.position.z;
		
		
		for(int k = 0; k < objeto[i].mesh.vertices.size(); ++k)
		{
			Vector3 v = {0,0,0};

			v = m2.Scale(objeto[i].mesh.vertices[k]);
			v = m1.Translate(v);

			objeto[i].mesh.vertices[k].x = v.x;
			objeto[i].mesh.vertices[k].y = v.y;
			objeto[i].mesh.vertices[k].z = v.z;
		}
		
	}
	
	/*
	vao = new GLuint;
	vbo = new GLuint;
	ibo = new GLuint;
	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);
	glGenBuffers(1, ibo);
	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, 0);
	double* bufferVertices;
	double* bufferIndices;
	glBufferData(GL_ARRAY_BUFFER, objeto.mesh.VerticesSize(), bufferVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objeto.mesh.FacesSize() , bufferIndices, GL_STATIC_DRAW);
*/

	// Habilita render de wireframes
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
	
	//cout<<objeto[1].mesh.vertices[1][0]<<endl;
	//cout<<objeto[1].mesh.faces[0][1][0]<<endl;

	cout<<GL_UNSIGNED_BYTE<<endl;
	glutMainLoop();
	exit(0);
}
