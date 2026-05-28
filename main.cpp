// arquivos de cabeçalho
#include <GL/freeglut.h>
#include <iostream>

// guardará a razão atual da largura e altura da janela
float aspecto = 1.0;

// guarda a posição atual da camera
float CamX = 1.0;
float CamY = 1.0;
float CamZ = 1.0;

float deltaTime{};
float lastFrame{};

// configura o campo de visualização
void confCamera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspecto, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(CamX, CamY, CamZ, 0, 0, 0, 0, 1, 0);
}


// funçao para quando houver redimensionamento da janela
void resize(int width, int height)
{
    if (height == 0)
        height = 1;
    aspecto = (float)width / height;
    glViewport(0, 0, width, height);
    confCamera();
}

// função responsável por eventos de teclado
void keyboard(unsigned char key, int posX, int posY)
{
    switch (key) {
        // saindo do programa
    case 27:
        exit(0);
        break;
    case 'x':
        glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
        break;

    case 'X':
        glRotatef(-5.0f, 1.0f, 0.0f, 0.0f);
        break;

    case 'y':
        glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
        break;

    case 'Y':
        glRotatef(-5.0f, 0.0f, 1.0f, 1.0f);
        break;

    case 'z':
        glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
        break;

    case 'Z':
        glRotatef(-5.0f, 0.0f, 0.0f, 1.0f);
        break;

    } 
    // repinta a tela
    glutPostRedisplay();
}



// função de desenho
void draw()
{
    float currentFrame{ (float)glutGet(GLUT_ELAPSED_TIME) };
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // desenhando o plano cartesiano 3D
    glBegin(GL_LINES);
    // eixo X
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-2.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    // eixo Y
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -2.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    // eixo Z
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -2.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 2.0);
    glEnd();

    //glLoadIdentity();
    //confCamera();

    glColor3f(1.0, 1.0, 1.0);
    glutWireCone(0.5, 0.5, 10, 10);

    glFlush();
}


// função para inicializar as variaveis de estado
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    confCamera();
    glEnable(GL_DEPTH_TEST);
}

// função principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    // configurando e exibindo uma janela
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("missao 1");

    // registrando função de callback
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);

    // inicialização das variáveis de estado
    init();

    // loop de tratamento de eventos
    glutMainLoop();

    return 0;
}