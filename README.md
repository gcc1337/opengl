<img width="1920" height="1080" alt="2026-05-15 20-56-33" src="https://github.com/user-attachments/assets/4f8fc606-97f1-4a52-b042-3480f600f6df" />
Estrutura da piramide:

```
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
```
