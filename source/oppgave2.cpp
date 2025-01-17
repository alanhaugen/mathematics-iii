#include "oppgave2.h"
#include "main.h"

oppgave2::oppgave2()
{
}

void oppgave2::Init()
{
    // Lag en 􏰂fil med datapunkter for en tredimensjonal spiral, som forklart i forelesningsnotater 2.4
    // Bestem selv en steglengde for parameteren t og verteksfarger. Benytt samme filformat som i forrige oppgave.
    float n = (2 * M_PI) * 5;

    float red = 1.0;
    float green = 0.0;

    float x = 0;
    float y = 0;

    float radius = 1.0f;
    float height = 0.0f;

    float step = 0.1;

    std::vector<Vertex> vertices;

    for (float i = 0; i < n; i+=step)
    {
        x = radius - cos(i);
        y = radius - sin(i);

        green += i / n; // gradient from 0.0 up to 1.0

        height += 0.01;

        // Store vertex in vertices list
        vertices.push_back(Vertex(x, y, height, red, green, 0.0f));
    }

    // Write to file
    dataFile = fopen("data2.txt", "w+");

    fprintf(dataFile, "%s%lu%s", "#", vertices.size(), "\n");

    for(const Vertex& v : vertices)
    {
        fprintf(dataFile, "%f %f %f %f %f %f%s", v.x, v.y, v.z, v.r, v.g, v.b, "\n");
    }

    fclose(dataFile);
}

void oppgave2::Update()
{
}
