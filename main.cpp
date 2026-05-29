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
    //confCamera();
}

// função responsável por eventos de teclado
void keyboard(unsigned char key, int posX, int posY)
{
    switch (key) {
        // saindo do programa
    case 27:
        exit(0);
        break;
    case 't':
        glTranslatef(1.0f, 0.0f, 0.0f);
        break;

    case 'T':
        glTranslatef(-1.0f, 0.0f, 0.0f);
        break;

    case 'y':
        glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
        break;

    case 'Y':
        glRotatef(-5.0f, 0.0f, 1.0f, 1.0f);
        break;

    case 'e':
        glScalef(1.0f, 1.0f, 1.5f);
        break;

    case 'E':
        glScalef(1.0f, 1.0f, 0.5f);
        break;
    }
    // repinta a tela
    glutPostRedisplay();
}

void drawShape(const std::vector<std::vector<float>>& points, const std::vector<std::vector<float>>& colors, GLenum mode)
{
    glBegin(mode);
    for (int i = 0; i < points.size(); i++)
    {
        glVertex3d(points[i][0], points[i][1], points[i][2]);
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
    }
    glEnd();
}

void hourglass()
{
    std::vector<float> A{ -1.0f, 0.0f, 0.0f };
    std::vector<float> B{ 0.0f, 1.0f, 0.0f };
    std::vector<float> C{ 1.0f, 0.0f, 0.0f };
    std::vector<float> D{ 0.5f, -1.0f, 0.0f };
    std::vector<float> E{ -0.5f, -1.0f, 0.0f };
    std::vector<float> picoPiramide{ 0.0f, 0.0f, 1.0f };

    std::vector<float> red{ 1.0f, 0.0f, 0.0f };
    std::vector<float> green{ 0.0f, 1.0f, 0.0f };
    std::vector<float> blue{ 0.0f, 0.0f, 1.0f };
    std::vector<float> yellow{ 1.0f, 1.0f, 0.0f };
    std::vector<float> cian{ 0.0f, 1.0f, 1.0f };
    std::vector<float> pink{ 1.0f, 0.0f, 1.0f };

    std::vector<std::vector<float>> posBase{
        A,
        B,
        C,
        D,
        E
    };

    std::vector<std::vector<float>> colorBase{
        red,
        green,
        blue,
        yellow,
        cian,
    };

    std::vector<std::vector<std::vector<float>>> triangles1{
        {{A, B, picoPiramide},
         {B, C, picoPiramide},
         {C, D, picoPiramide},
         {D, E, picoPiramide},
         {E, A, picoPiramide}}
    };
    for (auto& tri : triangles1)
        for (auto& pos : tri) {
            pos[2] -= 1;
        }

    std::vector<float> picoPiramideInvertida{ 0.0f, 0.0f, -1.0f };
    std::vector<std::vector<std::vector<float>>> triangles2{
        {{A, B, picoPiramideInvertida},
         {B, C, picoPiramideInvertida},
         {C, D, picoPiramideInvertida},
         {D, E, picoPiramideInvertida},
         {E, A, picoPiramideInvertida}}
    };
    for (auto& tri : triangles2)
        for (auto& pos : tri) {
            pos[2] += 1;
        }

    std::vector<std::vector<std::vector<float>>> colorTriangles{
        {{red, pink, green},
         {green, pink, blue},
         {blue, pink, yellow},
         {yellow, pink, cian},
         {cian, pink, red}}
    };

    auto posBase1 = posBase;
    for (auto& vec : posBase1)
        vec[2] = -1;

    auto posBase2 = posBase;
    for (auto& vec : posBase2)
        vec[2] = 1;


    drawShape(posBase1, colorBase, GL_POLYGON);

    for (int i = 0; i < triangles1.size(); i++)
    {
        drawShape(triangles1[i], colorTriangles[i], GL_TRIANGLES);
    }

    drawShape(posBase2, colorBase, GL_POLYGON);

    for (int i = 0; i < triangles2.size(); i++)
    {
        drawShape(triangles2[i], colorTriangles[i], GL_TRIANGLES);
    }

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
    //glutWireCone(0.5, 0.5, 10, 10);
    hourglass();

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
    glutCreateWindow("missao 2");

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