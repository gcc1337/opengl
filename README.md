<img width="1920" height="1080" alt="2026-05-15 19-51-58" src="https://github.com/user-attachments/assets/0e8c7a28-f024-4cea-9d3b-54c5ad6e40be" />

Controles de camera, com visualização em 1, 2, 3 e com WASD

```
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
```

Codigo que cria os vertices do paralelepípedo 
```
    std::vector<std::vector<float>> pos{
        //atras
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f},

        //frente
        {0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 0.5f, 1.0f},
        {0.0f, 0.5f, 1.0f},

        //esquerda
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.5f, 0.0f},
        {0.0f, 0.5f, 1.0f},
        {0.0f, 0.0f, 1.0f},

        //direita
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.5f, 0.0f},
        {1.0f, 0.5f, 1.0f},
        {1.0f, 0.0f, 1.0f},


        //baixo
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        
        //cima
        {0.0f, 0.5f, 0.0f},
        {1.0f, 0.5f, 0.0f},
        {1.0f, 0.5f, 1.0f},
        {0.0f, 0.5f, 1.0f}
    };

    float cor[] = { 0.3, 0.6, 0.8 };

    glBegin(GL_QUADS);
        for (int i = 0; i < pos.size(); i++)
        {
            glVertex3d(pos[i][0] - 0.5f, pos[i][1] - 0.25f, pos[i][2] - 0.5f);
            glColor3f(cor[0]+ i * 0.01f, cor[1]+ i * 0.02f, cor[2]+ i * 0.03f);
        }
    glEnd();
```
