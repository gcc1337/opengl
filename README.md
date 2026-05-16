<img width="800" height="450" alt="2026-05-1521-11-21-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/64b21cb1-b7e1-4bda-9336-97e40bc1c371" />

Implementação da função de desenhar, recebe os pontos do vertice, a cor de cada vertice, e o modo para ser desenhado

```

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

```

O formato do objeto abstrato, uma ampulheta!
```

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


```
