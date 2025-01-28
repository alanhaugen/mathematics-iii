#include <core/application.h>
#include <core/components/fpscamera.h>
#include "oppgave2.h"
#include "main.h"

oppgave2::oppgave2()
{
    Camera* cam = new Camera(0.0f, 0.0f, 10.0f);
    Text* text = new Text("oppgave 2");

    components.Add(cam);
    components.Add(text);
    components.Add(new FPSCamera(cam));
}

IDrawable *oppgave2::LoadFromFile(String filename)
{
    Array<unsigned int> indices;
    Array<String> shaders(2);

    ssize_t read;
    char * line = NULL;
    size_t len = 0;

    dataFile = fopen(filename.ToChar(), "r+");

    Array<IDrawable::Vertex> vertices;

    bool isFirstLine = true;
    bool firstPoint  = true;
    int numberOfVerteces = 0;

    float x;
    float y;
    float z;
    float red, green;

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

            red = atof(vertex.SubString(vertex.IndexOf(" ") + 1,
                                        vertex.IndexOf(" ", vertex.IndexOf(" ") + 1)).ToChar());
            green = atof(vertex.SubString(vertex.IndexOf(" ") + 1,
                                          vertex.IndexOf(" ", vertex.IndexOf(" ") + 1)).ToChar());

            vertices.Add(IDrawable::Vertex(glm::vec3(x, y, z), glm::vec4(red, green, 1.0f, 1.0f)));

            if (firstPoint == true)
            {
                firstPoint = false;
            }
            else
            {
                vertices.Add(IDrawable::Vertex(glm::vec3(x, y, z), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)));
            }
        }
    }

    fclose(dataFile);

    IFile *simpleVertShader = filesystem->Open(URL("data/simple.vert"), PLAIN_TEXT);
    IFile *simpleFragShader = filesystem->Open(URL("data/simple.frag"), PLAIN_TEXT);

    shaders.Insert(simpleVertShader->Read(), VERTEX_SHADER);
    shaders.Insert(simpleFragShader->Read(), FRAGMENT_SHADER);

    delete simpleVertShader;
    delete simpleFragShader;

    IDrawable* lines = renderer->CreateDrawable(vertices, indices, shaders);
    lines->type = DRAW_LINES;

    return lines;
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

    drawable = LoadFromFile("data2.txt");
}

void oppgave2::Update()
{
    if (input.Pressed(input.Key.RIGHT))
    {
        Application::NextScene();
    }

    renderer->Draw(drawable);
}
