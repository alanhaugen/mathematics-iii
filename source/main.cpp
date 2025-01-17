#include <core/application.h>
#include "oppgave1.h"
#include "oppgave2.h"
#include "oppgave3.h"

int main(int argc, char **argv)
{
    Application application(argc, argv);

    //application.AddScene(new oppgave1());
    application.AddScene(new oppgave2());
    //application.AddScene(new oppgave3());

    return application.Exec();
}

