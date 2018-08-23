/*
 * Main.cpp
 *
 *  Created on: 21 de ago de 2018
 *      Author: joao
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <GL/glut.h>

#include "Vector3.cpp"


using namespace std;

std::ostream& operator<<(std::ostream& o, Vector3 b){return b.dump(o);}
//continuaçao do toString


GLdouble windowWidth  = 800.0;
GLdouble windowHeight = 600.0;

int window;


// Callback do GLUT: Loop de display
void _Display(void)
{
	// Teste com uma linha
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	
	glVertex2f(0.25 * windowWidth,0.75 * windowHeight);
	glVertex2f(0.75 * windowWidth,0.25 * windowHeight);
	
	glEnd();
	glFlush();
}

// Callback do GLUT: Chamado na criação da janela e toda vez que ela for redimensionada
void _Redimensionar(int w, int h)
{
	// Redimensionamento bloqueado
	glutReshapeWindow(windowWidth, windowHeight);
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
	Vector3 teste(0,0,0);
	Vector3 teste2(10,1,1);
	teste=teste.Soma(teste2);
	cout<<teste<<endl;
	teste=teste.Subtracao(teste);
	cout<<teste<<endl;

	// Inicialização do GLUT e janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int) windowWidth, (int) windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)- windowWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)- windowHeight)/2);
	window = glutCreateWindow("CG");
	
	// Inicialização do viewport e projeção
	glViewport(0, 0, (GLsizei) windowWidth, (GLsizei) windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.f, 1.f);

	// Definição de callbacks
	glutReshapeFunc(_Redimensionar);
	glutKeyboardFunc(_Teclado);
	glutDisplayFunc(_Display);

	// Definição de cor de fundo,  cor de desenho e espessura da linha de teste
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);


	glutMainLoop();

	exit(0);
}

