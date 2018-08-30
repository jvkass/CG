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


Mesh meshTeste;

// Callback do GLUT: Loop de display
void _Display(void)
{
	// Teste com uma linha
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	
	for(int i = 0; i < meshTeste.faces.size(); ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			glVertex3d(*meshTeste.vertices[meshTeste.faces[i][j][0] - 1][0] * 1,
					*meshTeste.vertices[meshTeste.faces[i][j][0] - 1][1] * 1,
						*meshTeste.vertices[meshTeste.faces[i][j][0] - 1][2]);
		}
	}
	
	glEnd();
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
	gluLookAt(2.0, 2.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
		default:
			break;
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
	Matrix m1(4, 4);
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
	
	Matrix m4(4, 4);
	m4[0][0] = 1;
	m4[0][3] = 2;
	m4[1][1] = 1;
	m4[1][3] = -1;
	m4[2][2] = 1;
	m4[2][3] = 4;
	m4[3][3] = 1;
	
	Matrix m5(4, 4);
	m5[0][0] = 2;
	m5[1][1] = 2;
	m5[2][2] = 2;
	m5[3][3] = 1;
	
	Matrix m6(4, 4);
	
	Vector3 v2(0,1,0);
	
	cout << (m1 + m2).toString() << endl;
	cout << (m2 - m1).toString() << endl;
	cout << (m1	* 2).toString() << endl;
	cout << (m1 / 2).toString() << endl;
	cout << m3.toString() << endl;
	cout << m3.Transpose().toString() << endl;
	cout << (m1 * m2).toString() << endl;
	cout << (m1 * v1).toString() << endl;
	cout << m4.toString() << endl;
	cout << v1.toString() << endl;
	cout << m4.Translate(v1).toString() << endl;
	cout << m5.Scale(v1).toString() << endl;
	cout << m6.Rotate(v2, 90, 'x').toString() << endl;
	
	
	// Test load Obj
	meshTeste = LoadObj("cube.obj");

	// Inicialização do GLUT e janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int) windowWidth, (int) windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)- windowWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)- windowHeight)/2);
	window = glutCreateWindow("CG");

	// Definição de callbacks
	glutReshapeFunc(_Redimensionar);
	glutKeyboardFunc(_Teclado);
	glutDisplayFunc(_Display);

	// Definição de cor de fundo,  cor de desenho e espessura da linha de teste
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	
	// Habilita render de wireframes
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glutMainLoop();

	exit(0);
}

