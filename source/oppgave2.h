#ifndef oppgave2_H
#define oppgave2_H

#include <core/x-platform/scene.h>

class oppgave2 : public IScene
{
public:
    oppgave2();

    FILE* dataFile;

    IDrawable *LoadFromFile(String filename);
    IDrawable* drawable;

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
