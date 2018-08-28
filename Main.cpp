#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <GL/glut.h>


#include "Vector3.cpp"
using namespace std;
std::ostream& operator<<(std::ostream& o, Vector3 b){return b.dump(o);}
//continuaçao do toString

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
	// Teste Vector3
	/*Vector3 teste(0,0,0);
	Vector3 teste2(10,1,1);
	teste = teste . Soma(teste2);
	cout << teste << endl;
	teste = teste . Subtracao(teste);
	cout << teste << endl;*/
	
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

