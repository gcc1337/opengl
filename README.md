<img width="800" height="450" alt="ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/e1c537c8-b371-496a-8404-b49b02845720" />

As diferentes posições da camera:
```
// função responsável por eventos de teclado
void keyboard(unsigned char key, int posX, int posY)
{
    switch (key) {
        // saindo do programa
    case 27:
        exit(0);
        break;
    case 'q':
        CamX = 0.0;
        CamY = 0.0;
        CamZ = 1.0;
        glClearColor(1.0, 0.0, 0.0, 0.0);
        break;
    case 'w':
        CamX = 1.0;
        CamY = 0.0;
        CamZ = 0.0;
        glClearColor(0.0, 1.0, 0.0, 0.0);
        glClearColor(0.0, 1.0, 0.0, 0.0);
        break;

    case 'e':
        CamX = 0.0;
        CamY = 2.0;
        CamZ = 0.001;
        glClearColor(0.0, 0.0, 1.0, 0.0);
        break;

    } 
    // repinta a tela
    glutPostRedisplay();
}

```
