#ifndef oppgave2_H
#define oppgave2_H

#include <core/x-platform/scene.h>

class oppgave2 : public IScene
{
public:
    oppgave2();

    FILE* dataFile;

    void Init();
    void Update();
};

#endif
