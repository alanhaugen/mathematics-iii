#ifndef oppgave3_H
#define oppgave3_H

#include <core/x-platform/scene.h>

class oppgave3 : public IScene
{
public:
    oppgave3();

    FILE* dataFile;

    IDrawable *LoadFromFile(String filename);
    IDrawable* drawable;

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
