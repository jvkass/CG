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

#include "Vector3.cpp"
#include "Vector4.cpp"
#include "Matrix.cpp"
#include "Mesh.cpp"
#include "Transform.cpp"
#include "GameObject.cpp"


GLdouble windowWidth  = 800.0;
GLdouble windowHeight = 600.0;

int window;



GameObject objeto[20];

GLuint* vao;
GLuint* vbo;
GLuint* ibo;

float kEpsilon = 0.000001;

Vector3 crossProduct(Vector3 point1, Vector3 point2){

  Vector3 vector; 

  vector.x = point1.y * point2.z - point2.y * point1.z; 
  vector.y = point2.x * point1.z - point1.x * point2.z; 
  vector.z = point1.x * point2.y - point1.y * point2.x; 

  return vector;
}

float dotProduct(Vector3 dot1, Vector3 dot2){

  float dot = dot1.x * dot2.x + dot1.y * dot2.y + dot1.z * dot2.z; 

  return dot;
}

bool RayIntersectsTriangle(Vector3 orig, Vector3 dir, Vector3 p0, Vector3 p1, Vector3 p2)
{
// compute plane's normal

  Vector3 p0p1, p0p2;

  p0p1.x = p1.x - p0.x; 
  p0p1.y = p1.y - p0.y; 
  p0p1.z = p1.z - p0.z; 

  p0p2.x = p2.x - p0.x;
  p0p2.x = p2.x - p0.x;
  p0p2.y = p2.y - p0.y; 
  p0p2.z = p2.z - p0.z;

  // no need to normalize
  Vector3 N = crossProduct(p0p1, p0p2); // N 

  // Step 1: finding P

  // check if ray and plane are parallel ?
  float NdotRayDirection = dotProduct(N, dir); // if the result is 0, the function will return the value false (no intersection).

  if (fabs(NdotRayDirection) < kEpsilon){ // almost 0 

      return false; // they are parallel so they don't intersect ! 
  }

  // compute d parameter using equation 2
  float d = dotProduct(N, p0); 

  // compute t (equation P=O+tR P intersection point ray origin O and its direction R)

  float t = -((dotProduct(N, orig) - d) / NdotRayDirection);

  // check if the triangle is in behind the ray
  //if (t < 0){ return false; } // the triangle is behind 

  // compute the intersection point using equation
  Vector3 P; 

  //this part should do the work, but it does not work.
  P.x = orig.x + t * dir.x; 
  P.y = orig.y + t * dir.y; 
  P.z = orig.z + t * dir.z; 


  // Step 2: inside-outside test
  Vector3 C; // vector perpendicular to triangle's plane 

  // edge 0
  Vector3 edge0; 

  edge0.x = p1.x - p0.x;
  edge0.y = p1.y - p0.y;
  edge0.z = p1.z - p0.z;

  Vector3 vp0; 

  vp0.x = P.x - p0.x;
  vp0.y = P.y - p0.y; 
  vp0.z = P.z - p0.z; 

  C = crossProduct(edge0, vp0); 

  if (dotProduct(N, C) < 0) { return false; }// P is on the right side 

  // edge 1
  Vector3 edge1;

  edge1.x = p2.x - p1.x;
  edge1.y = p2.y - p1.y;
  edge1.z = p2.z - p1.z;

  Vector3 vp1; 

  vp1.x = P.x - p1.x; 
  vp1.y = P.y - p1.y; 
  vp1.z = P.z - p1.z; 

  C = crossProduct(edge1, vp1); 

  if (dotProduct(N, C) < 0) { return false; } // P is on the right side 

  // edge 2
  Vector3 edge2;

  edge2.x = p0.x - p2.x;    
  edge2.y = p0.y - p2.y;
  edge2.z = p0.z - p2.z;

  Vector3 vp2; 

  vp2.x = P.x - p2.x;
  vp2.y = P.y - p2.y;
  vp2.z = P.z - p2.z;

  C = crossProduct(edge2, vp2);

  if (dotProduct(N, C) < 0) { return false; } // P is on the right side; 

  return true; // this ray hits the triangle 
}

// Callback do GLUT: Loop de display
void _Display(void)
{
	// Teste com uma linha
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	
	glPointSize(3);
	
	glBegin(GL_POINTS);
	for(int i = 0; i < windowWidth/3; ++i)
	{
		for(int j = 0; j < windowHeight/3; ++j)
		{
			if(RayIntersectsTriangle({0,0,-1}, {(double)i,(double)j, 1}, {-100,-100,0}, {0,100,0}, {100,-100,0}))
			{
				glColor3d(1,0,0);
				glVertex2d((i * 3 - windowWidth/2), (j * 3 - windowHeight/2));
			}
			else
			{
				glColor3d(0,0,0.5f);
				glVertex2d((i * 3 - windowWidth/2), (j * 3 - windowHeight/2));
			}
		}
	}
	glEnd();

	/*for(int k = 0; k < 20; ++k)
	{
		glPushMatrix();
		
		glColor3d(objeto[k].color.x, objeto[k].color.y, objeto[k].color.z);
		//glRotated(objeto[k].transform.rotation.x, objeto[k].transform.rotation.y, objeto[k].transform.rotation.z, 0.0);
		
		glBegin(GL_TRIANGLES);
		for(int i = 0; i < objeto[k].mesh.faces.size(); ++i)
		{
			for(int j = 0; j < 3; ++j)
			{
				glVertex3d(objeto[k].mesh.vertices[objeto[k].mesh.faces[i][j][0] - 1][0],
								objeto[k].mesh.vertices[objeto[k].mesh.faces[i][j][0] - 1][1],
									objeto[k].mesh.vertices[objeto[k].mesh.faces[i][j][0] - 1][2]);
			}
		}
		glEnd();
		
		
		glPopMatrix();
	}*/
	
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
	cout << teste5.Reflect(&plano[0]).toString() << endl;
	
	
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowSize((int) windowWidth, (int) windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)- windowWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)- windowHeight)/2);
	window = glutCreateWindow("CG");
	  
	glewExperimental = GL_TRUE; 
	glewInit(); 
	
	
	// Definição de callbacks
	glutReshapeFunc(_Redimensionar);
	glutKeyboardFunc(_Teclado);
	glutMotionFunc(_Mouse);
	glutDisplayFunc(_Display);

	
	// Definição de cor de fundo,  cor de desenho e espessura da linha de teste
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	
	
	for(int i = 0; i < 20; ++i)
	{
		LoadObj("cube.obj", &objeto[i].mesh);
		
		objeto[i].color = Vector3{((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX))};
		objeto[i].transform.scale = Vector3{(double)(rand() % 200), (double)(rand() % 200), (double)(rand() % 200)};
		objeto[i].transform.rotation = Vector3{(double)(rand() % 360), (double)(rand() % 360), (double)(rand() % 360)};
		
		objeto[i].transform.position = Vector3{(double)(rand() % (int)windowWidth) - windowWidth/2, (double)(rand() % (int)windowHeight) - windowHeight/2, 0};
		
		Matrix m3{4, 4};
		m3[0][0] = 1;
		m3[1][1] = 1;
		m3[2][2] = 1;
		m3[3][3] = 1;
		
		Matrix m2{4, 4};
		m2[0][0] = objeto[i].transform.scale.x;
		m2[1][1] = objeto[i].transform.scale.x;
		m2[2][2] = objeto[i].transform.scale.x;
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
			Vector3 v = m3.Rotate(Vector3(objeto[i].mesh.vertices[k][0], objeto[i].mesh.vertices[k][1], objeto[i].mesh.vertices[k][2]), objeto[i].transform.rotation.x, 'x');
			v = m3.Rotate(Vector3(objeto[i].mesh.vertices[k][0], objeto[i].mesh.vertices[k][1], objeto[i].mesh.vertices[k][2]), objeto[i].transform.rotation.y, 'y');
			v = m3.Rotate(Vector3(objeto[i].mesh.vertices[k][0], objeto[i].mesh.vertices[k][1], objeto[i].mesh.vertices[k][2]), objeto[i].transform.rotation.z, 'z');
			
			v = m2.Scale(Vector3(objeto[i].mesh.vertices[k][0], objeto[i].mesh.vertices[k][1], objeto[i].mesh.vertices[k][2]));
			
			v = m1.Translate(Vector3(objeto[i].mesh.vertices[k][0], objeto[i].mesh.vertices[k][1], objeto[i].mesh.vertices[k][2]));
												
			objeto[i].mesh.vertices[k].x = v.x;
			objeto[i].mesh.vertices[k].y = v.y;
			objeto[i].mesh.vertices[k].z = v.z;
		}
		
	}
	
	/*vao = new GLuint;
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objeto.mesh.FacesSize() , bufferIndices, GL_STATIC_DRAW);*/
	
	
	// Habilita render de wireframes
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glutMainLoop();

	exit(0);
}

