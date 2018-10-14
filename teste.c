#include <IL/il.h>
#include <GL/glut.h>
 
 
#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480
 
int width  = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;
 
/* Manipulador para evento de repintura de janelas. Chamado de volta quando a janela aparece pela primeira vez e
    sempre que a janela precisar ser pintada novamente. */
void display() 
{
    // Limpar cor e profundidade buffers
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
       glMatrixMode(GL_MODELVIEW);     // Operar na matriz de visualização de modelo
 
    
       glBegin(GL_QUADS);
           glTexCoord2i(0, 0); glVertex2i(0,   0);
           glTexCoord2i(0, 1); glVertex2i(0,   height);
           glTexCoord2i(1, 1); glVertex2i(width, height);
           glTexCoord2i(1, 0); glVertex2i(width, 0);
       glEnd();
 
    glutSwapBuffers();
} 
 
/* Manipulador para evento de redimensionamento de janela. Chamado de volta quando a janela aparece pela primeira vez e
    sempre que a janela é redimensionada com sua nova largura e altura */
void reshape(GLsizei newwidth, GLsizei newheight) 
{  
    // Definir a viewport para cobrir a nova janela
       glViewport(0, 0, width=newwidth, height=newheight);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(0.0, width, height, 0.0, 0.0, 100.0);
     glMatrixMode(GL_MODELVIEW);
 
    glutPostRedisplay();
}
 
 
/* Inicializar gráficos OpenGL*/
void initGL(int w, int h) 
{
     glViewport(0, 0, w, h); // use um tamanho de tela de WIDTH x HEIGHT
     glEnable(GL_TEXTURE_2D);     // Ativar texturização 2D
 
    glMatrixMode(GL_PROJECTION);     // Faça uma projeção 2D simples em toda a janela
     glLoadIdentity();
     glOrtho(0.0, w, h, 0.0, 0.0, 100.0);
 
     glMatrixMode(GL_MODELVIEW);    // Definir o modo de matriz para modelagem de objetos
 
     glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
     glClearDepth(0.0f);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpar a Janela
}
 
/* Carregue uma imagem usando DevIL e retorne o manipulador devIL (-1 se falhar) */
int LoadImage(char *filename)
{
    ILboolean success; 
     ILuint image; 
 
    ilGenImages(1, &image); /* Geração de um nome de imagem */
     ilBindImage(image); /* Binding of image name */
     success = ilLoadImage(filename); /* Loading of the image filename by DevIL */
 
    if (success) /* If no error occured: */
    {
        /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
           success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
 
        if (!success)
           {
                 return -1;
           }
    }
    else
        return -1;
 
    return image;
}
 
int main(int argc, char **argv) 
{
 
    GLuint texid;
    int    image;
 
    if ( argc < 1)
    {
        /* no image file to  display */
        return -1;
    }
 
    /* GLUT init */
    glutInit(&argc, argv);            // Initialize GLUT
       glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
       glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);   // Set the window's initial width & height
       glutCreateWindow(argv[0]);      // Create window with the name of the executable
       glutDisplayFunc(display);       // Register callback handler for window re-paint event
       glutReshapeFunc(reshape);       // Register callback handler for window re-size event
 
    /* OpenGL 2D generic init */
    initGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);
 
    /* Initialization of DevIL */
     if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
     {
           printf("wrong DevIL version \n");
           return -1;
     }
     ilInit(); 
 
 
    /* load the file picture with DevIL */
    image = LoadImage(argv[1]);
    if ( image == -1 )
    {
        printf("Can't load picture file %s by DevIL \n", argv[1]);
        return -1;
    }
 
    /* OpenGL texture binding of the image loaded by DevIL  */
       glGenTextures(1, &texid); /* Texture name generation */
       glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
        0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
 
    /* Main loop */
    glutMainLoop();
 
    /* Delete used resources and quit */
     ilDeleteImages(1, &image); /* Because we have already copied image data into texture data we can release memory used by image. */
     glDeleteTextures(1, &texid);
 
     return 0;
}
