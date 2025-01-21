#include <core/application.h>
#include "oppgave3.h"
#include "main.h"

oppgave3::oppgave3()
{
    Camera* cam = new Camera();

    components.Add(cam);
    components.Add(new Text("oppgave 3"));
}

void oppgave3::Init()
{
    // Velg funksjonen av to variable som vi kaller apesadelen, f(x) = x^2y, et passende område i
    // xy-planet (eller xz-planet), og en oppdeling. Velg en oppløsning h (bruk en grov oppløsning
    // til å begynne med) og regn ut funksjonsverdier over området, som på 􏰂figur 2.2. Lag en tekst􏰂fil
    // med xyz (eventuelt også rgb og uv-koordinater) linjevis. Antall linjer skal stå øverst i fila.
    std::vector<Vertex> vertices;

    float xmin=0.0f, xmax=1.0f, ymin=0.0f, ymax=1.0f, h=0.25f;
    for (float x=xmin; x<xmax; x+=h)
    {
        for (float y=ymin; y<ymax; y+=h)
        {
            float z = sin(M_PI*x)*sin(M_PI*y);
            vertices.push_back(Vertex(x,y,z,x,y,z));
            z = sin(M_PI*(x+h))*sin(M_PI*y);
            vertices.push_back(Vertex(x+h,y,z,x,y,z));
            z = sin(M_PI*x)*sin(M_PI*(y+h));
            vertices.push_back(Vertex(x,y+h,z,x,y,z));
            vertices.push_back(Vertex(x,y+h,z,x,y,z));
            z = sin(M_PI*(x+h))*sin(M_PI*y);
            vertices.push_back(Vertex(x+h,y,z,x,y,z));
            z = sin(M_PI*(x+h))*sin(M_PI*(y+h));
            vertices.push_back(Vertex(x+h,y+h,z,x,y,z));
        }
    }

    // Write to file
    dataFile = fopen("data3.txt", "w+");

    fprintf(dataFile, "%s%lu%s", "#", vertices.size(), "\n");

    for(const Vertex& v : vertices)
    {
        fprintf(dataFile, "%f %f %f %f %f %f%s", v.x, v.y, v.z, v.r, v.g, v.b, "\n");
    }

    fclose(dataFile);
}

void oppgave3::Update()
{
}

void oppgave3::UpdateAfterPhysics()
{
}

