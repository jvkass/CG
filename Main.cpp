#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glut.h>


using namespace std;


#define RADIANOS_PARA_GRAUS 180 / 3.14159265358979323846f
#define GRAUS_PARA_RADIANOS 3.14159265358979323846f / 180

#include "Vector3.cpp"
#include "Vector4.cpp"
#include "Matrix.cpp"
#include "Mesh.cpp"


GLdouble windowWidth  = 800.0;
GLdouble windowHeight = 600.0;

int window;


int mouse[2];

Vector3 camera(0, 0, 0);
Vector3 cameraLook(0, 0, 0);
Vector3 cameraUp(0, 1, 0);
Vector3 cameraSpeed(0.1f, 0.08f, 0.5f);
Matrix cameraRotation(4, 4);


Mesh meshObjeto;
unsigned int objeto;

// Callback do GLUT: Loop de display
void _Display(void)
{
	// Teste com uma linha
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	glLoadIdentity();
	glTranslated(camera[0], camera[1], camera[2]);
	glRotatef(cameraLook[0], 0.0f, 1.0, 0.0f);
	glRotatef(-cameraLook[1], 1.0f, 0.0f, 0.0f);
	gluLookAt(5, 5, 5, 0, 0, 0, cameraUp[0], cameraUp[1], cameraUp[2]);
	
	
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glCallList(objeto);
	glPopMatrix();
	
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(2, 0.0, -3.0);
	glRotatef(99.0, 0.0, 0.0, 1.0);
	glCallList(objeto);
	glPopMatrix();
	
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(-3.5, 0.0, 3.0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(15.0, 0.0, 0.0, 1.0);
	glCallList(objeto);
	glPopMatrix();
	
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(2, 0.5, 1);
	glTranslatef(0.0, -3.0, 1);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glCallList(objeto);
	glPopMatrix();
	glFlush();
}

// Callback do GLUT: Chamado na criação da janela e toda vez que ela for redimensionada
void _Redimensionar(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	
	// Redefinição do viewport e projeção
	glViewport(0, 0, (GLsizei) windowWidth, (GLsizei) windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, windowWidth/windowHeight, 0, 10);
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
		case 32:
			cameraLook = Vector3(0,0,0);
			camera = Vector3(0,0,0);
			
			mouse[0] = 0;
			mouse[1] = 0;
			break;
		case 'a':
			camera[0] += cameraSpeed[2];
			break;
		case 'd':
			camera[0] -= cameraSpeed[2];
			break;
		case 'o':
			camera[1] -= cameraSpeed[2];
			break;
		case 'l':
			camera[1] += cameraSpeed[2];
			break;
		case 'w':
			camera[2] += cameraSpeed[2];
			break;
		case 's':
			camera[2] -= cameraSpeed[2];
			break;
	}
	
	glutPostRedisplay();
}

// Callback do GLUT: Eventos de mouse com algum botão pressionado
void _Mouse(int x, int y)
{
	int oldX = mouse[0];
	int oldY = mouse[1];
	
	mouse[0] = x;
	mouse[1] = y;
	
	if(mouse[0] != oldX || mouse[1] != oldY)
	{
		double rotateX = 0;
		double rotateY = 0;
		
		if(mouse[0] > oldX)
		{
			rotateX = cameraSpeed[0];
		}
		else if(mouse[0] < oldX)
		{
			rotateX = -cameraSpeed[0];
		}
		
		if(mouse[1] > oldY)
		{
			rotateY = -cameraSpeed[1];
		}
		else if(mouse[1] < oldY)
		{
			rotateY = cameraSpeed[1];
		}
		
		cameraLook[0] += rotateX;
		cameraLook[1] += rotateY;
		//cameraLook = cameraRotation.Rotate(cameraLook, 'y', rotateY);
	
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[])
{
	//Testes Vector3
	/*Vector3 teste1(0,0,0);
	Vector3 teste2(1,1,1);
	Vector3 teste3(3,4,-10);
	Vector3 teste4(12,-2,-3);
	Vector3 teste5(0.5f,0.5f,0.5f);
	
	Vector3 plano[3] = {Vector3(0,0,0),Vector3(0,1,0),Vector3(0,1,1)};
	
	cout << teste2.Magnitude() << endl;
	cout << teste2.MagnitudeSquared() << endl;
	cout << teste2.Normalize().toString() << endl;
	cout << (teste2 + teste3).toString() << endl;
	cout << (teste2 - teste3).toString() << endl;
	cout << (teste2 * 2).toString() << endl;
	cout << (teste2 / 2).toString() << endl;
	cout << (teste2 == teste2) << endl;
	cout << (teste2 == teste1) << endl;
	cout << (teste2 == teste3) << endl;
	cout << (teste2 != teste4) << endl;
	cout << teste2.Dot(teste3) << endl;
	cout << teste2.Cross(teste3).toString() << endl;
	cout << teste2.Angle(teste3) << endl;
	cout << teste5.Reflect(&plano[0]).toString() << endl;*/
	
	
	//Testes Matrix
	/*Matrix m1(4, 4);
	m1[0][0] = 0;
	m1[0][1] = 1;
	m1[0][2] = 1;
	m1[2][2] = 1;
	
	Matrix m2(4, 4);
	m2[0][0] = 2;
	m2[1][0] = 2;
	m2[2][0] = 2;
	m2[3][0] = 2;
	
	Matrix m3(4, 2);
	m3[0][1] = 1;
	m3[3][0] = 1;
	
	Vector3 v1(3,7,5);
	
	cout << (m1 + m2).toString() << endl;
	cout << (m2 - m1).toString() << endl;
	cout << (m1	* 2).toString() << endl;
	cout << (m1 / 2).toString() << endl;
	cout << m3.toString() << endl;
	cout << m3.Transpose().toString() << endl;
	cout << (m1 * m2).toString() << endl;
	cout << (m1 * v1).toString() << endl;*/

	
	// Inicialização do GLUT e janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int) windowWidth, (int) windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)- windowWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)- windowHeight)/2);
	window = glutCreateWindow("CG");
	
	
	// Definição de callbacks
	glutReshapeFunc(_Redimensionar);
	glutKeyboardFunc(_Teclado);
	glutMotionFunc(_Mouse);
	glutDisplayFunc(_Display);

	
	// Definição de cor de fundo,  cor de desenho e espessura da linha de teste
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	
	
	// Definição da Draw List e load do objeto
	meshObjeto = LoadObj("cube.obj");
	
	objeto = glGenLists(1);
	glNewList(objeto, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	
	for(int i = 0; i < meshObjeto.faces.size(); ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			glVertex3d(meshObjeto.vertices[meshObjeto.faces[i][j][0] - 1][0] * 1,
					meshObjeto.vertices[meshObjeto.faces[i][j][0] - 1][1] * 1,
						meshObjeto.vertices[meshObjeto.faces[i][j][0] - 1][2]);
		}
	}
	
	glEnd();
	glEndList();
	
	// Habilita render de wireframes
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glutMainLoop();

	exit(0);
}

