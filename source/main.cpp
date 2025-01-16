#include <core/application.h>
#include "oppgave1.h"
#include "oppgave2.h"

int main(int argc, char **argv)
{
    Application application(argc, argv);

    application.AddScene(new oppgave1());
    application.AddScene(new oppgave2());

    return application.Exec();
}

