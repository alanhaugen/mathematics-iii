#ifndef oppgave1_H
#define oppgave1_H

#include <core/x-platform/scene.h>

class oppgave1 : public IScene
{
public:
    oppgave1();

    FILE* dataFile;
    double h;

    struct Df{
        float a,b;

        Df(float a_, float b_)
        {
            a = a_;
            b = b_;
        }
    };

    Df d_f;
    unsigned int n;

    IDrawable* drawable;

    IDrawable *LoadFromFile(String filename);

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
