#include <core/application.h>
#include "oppgave3.h"
#include "main.h"

oppgave3::oppgave3()
{
    Camera* cam = new Camera();

    components.Add(cam);
    components.Add(new Text("oppgave 3"));
}

IDrawable *oppgave3::LoadFromFile(String filename)
{
    Array<unsigned int> indices;
    Array<String> shaders(2);

    ssize_t read;
    char * line = NULL;
    size_t len = 0;

    dataFile = fopen(filename.ToChar(), "r+");

    Array<IDrawable::Vertex> vertices;

    bool isFirstLine = true;
    int numberOfVerteces = 0;

    float x;
    float y;
    float z;

    while ((read = getline(&line, &len, dataFile)) != -1)
    {
        if (isFirstLine)
        {
            String firstLine(line);
            numberOfVerteces = atoi(firstLine.SubString(1, firstLine.Length()).ToChar());
            isFirstLine = false;
        }
        else
        {
            String vertex(line);

            x = atof(vertex.SubString(0, vertex.IndexOf(" ")).ToChar());
            y = atof(vertex.SubString(vertex.IndexOf(" ") + 1, vertex.IndexOf(" ", vertex.IndexOf(" ") + 1)).ToChar());
            z = atof(vertex.SubString(vertex.IndexOf(" ", vertex.IndexOf(" ") + 1),
                                      vertex.IndexOf(" ", vertex.IndexOf(" ", vertex.IndexOf(" ") + 1) + 1)).ToChar());

            vertices.Add(IDrawable::Vertex(glm::vec3(x * 10, y * 10, z * 10) - glm::vec3(5, 5, 0), glm::vec4(0.0f, y, z, 1.0f)));
        }
    }

    fclose(dataFile);

    shaders.Insert("data/simple.vert", VERTEX_SHADER);
    shaders.Insert("data/simple.frag", FRAGMENT_SHADER);

    IDrawable* mesh = renderer->CreateDrawable(vertices, indices, shaders);

    return mesh;
}

double f(const double x, const double y)
{
    // f(x, y) = x*x*y
    return x * x * y;

    // f(x, y) = sin πx · sin πy
    //return sin(M_PI*x)*sin(M_PI*y);
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
            float z = f(x, y);
            vertices.push_back(Vertex(x,y,z,x,y,z));
            z = f(x+h, y);
            vertices.push_back(Vertex(x+h,y,z,x,y,z));
            z = f(x, y+h);
            vertices.push_back(Vertex(x,y+h,z,x,y,z));
            vertices.push_back(Vertex(x,y+h,z,x,y,z));
            z = f(x+h, y);
            vertices.push_back(Vertex(x+h,y,z,x,y,z));
            z = f(x+h, y+h);
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

    drawable = LoadFromFile("data3.txt");
}

void oppgave3::Update()
{
    renderer->Draw(drawable);
}
