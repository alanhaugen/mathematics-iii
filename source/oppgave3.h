#ifndef oppgave3_H
#define oppgave3_H

#include <core/x-platform/scene.h>

class oppgave3 : public IScene
{
public:
    oppgave3();

    FILE* dataFile;

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
