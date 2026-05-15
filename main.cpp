// arquivos de cabeçalho
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

// guardará a razão atual da largura e altura da janela
float aspecto = 1.0;

// guarda a posição atual da camera
float CamX = 2.0;
float CamY = 2.0;
float CamZ = 2.0;

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
    case '1':
        CamX = 0.0;
        CamY = 0.0;
        CamZ = 2.0;
        //glClearColor(1.0, 0.0, 0.0, 0.0);
        break;
    case '2':
        CamX = 2.0;
        CamY = 0.0;
        CamZ = 0.0;
        //glClearColor(0.0, 1.0, 0.0, 0.0);
        break;
            
    case '3':
        CamX = 2.0;
        CamY = 2.0;
        CamZ = 2.0;
        //glClearColor(0.0, 0.0, 1.0, 0.0);
        break;

    case 'w':
        CamZ += 0.1;
        //glClearColor(1.0, 0.0, 0.0, 0.0);
        break;
    case 'a':
        CamX -= 0.1;
        //glClearColor(0.0, 1.0, 0.0, 0.0);
        break;

    case 's':
        CamZ -= 0.1;
        //glClearColor(0.0, 0.0, 1.0, 0.0);
        break;
    case 'd':
        CamX += 0.1;
        //glClearColor(0.0, 0.0, 1.0, 0.0);
        break;
    } 
    // repinta a tela
    glutPostRedisplay();
}


void retangle()
{
    std::vector<float> A{ -1.0f, 0.0f, 0.0f };
    std::vector<float> B{ 0.0f, 1.0f, 0.0f };
    std::vector<float> C{ 1.0f, 0.0f, 0.0f };
    std::vector<float> D{ 0.5f, -1.0f, 0.0f };
    std::vector<float> E{ -0.5f, -1.0f, 0.0f };
    std::vector<float> picoPiramide{ 0.0f, 0.0f, 1.0f };

    std::vector<std::vector<float>> posBase{
        A,
        B,
        C,
        D,
        E
    };
    
    std::vector<std::vector<std::vector<float>>> triangles{
        {{A, B, picoPiramide},
         {B, C, picoPiramide},
         {C, D, picoPiramide},
         {D, E, picoPiramide},
         {E, A, picoPiramide}}
    };

    float cor[] = { 0.3, 0.6, 0.8 };


    glBegin(GL_POLYGON);
        for (int i = 0; i < posBase.size(); i++)
        {
            glVertex3d(posBase[i][0], posBase[i][1], posBase[i][2]);
            glColor3f(cor[0]+ i * 0.01f, cor[1]+ i * 0.02f, cor[2]+ i * 0.03f);
        }
    glEnd();

    glBegin(GL_TRIANGLES);
    for (auto& tri : triangles)
    {
        for(auto& vec: tri)
            glVertex3d(vec[0], vec[1], vec[2]);
            glColor3f(cor[0] += 0.1, cor[1] += 0.2, cor[2] += 0.3);
    }
    glEnd();
}

// função de desenho
void draw()
{
    float currentFrame{ (float)glutGet(GLUT_ELAPSED_TIME) };
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // desenhando o plano cartesiano 3D
    //glBegin(GL_LINES);
    //// eixo X
    //glColor3f(0.0, 0.0, 0.0);
    //glVertex3f(-2.0, 0.0, 0.0);
    //glColor3f(1.0, 0.0, 0.0);
    //glVertex3f(2.0, 0.0, 0.0);
    //// eixo Y
    //glColor3f(0.0, 0.0, 0.0);
    //glVertex3f(0.0, -2.0, 0.0);
    //glColor3f(0.0, 1.0, 0.0);
    //glVertex3f(0.0, 2.0, 0.0);
    //// eixo Z
    //glColor3f(0.0, 0.0, 0.0);
    //glVertex3f(0.0, 0.0, -2.0);
    //glColor3f(0.0, 0.0, 1.0);
    //glVertex3f(0.0, 0.0, 2.0);
    //glEnd();

    glLoadIdentity();
    confCamera();

    glColor3f(1.0, 1.0, 1.0);
    //glutWireCone(0.5, 0.5, 10, 10);
    retangle();

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
    glutCreateWindow("missao 3");

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