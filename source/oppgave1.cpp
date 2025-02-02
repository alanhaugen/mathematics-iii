#include <core/application.h>
#include <core/components/fpscamera.h>
#include <core/components/triangle.h>
#include <core/components/cube.h>
#include <stdlib.h>
#include "oppgave1.h"
#include "main.h"

// I denne oppgaven skal du lage datapunkter for grafen til en funksjon,
// og punktene skal lagres på en tekstfil med format som forklart på forelesning (Verteksdata linjevis)

oppgave1::oppgave1() :
    d_f(0,0)
{
    Camera* cam = new Camera(0.0f, 0.0f, 10.0f);

    components.Add(cam);
    components.Add(new FPSCamera(cam));
    components.Add(new Text("oppgave 1"));
    components.Add(new Text("f(x) = x^3 - 6x^2 + 11x - 6", 0.0f, 100.0f));
}

IDrawable *oppgave1::LoadFromFile(String filename)
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

    float blue;
    float green;

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

            x = atof(vertex.SubString(0,
                                      vertex.IndexOf(" ")).ToChar());
            y = atof(vertex.SubString(vertex.IndexOf(" ") + 1,
                                      vertex.IndexOf(" ", vertex.IndexOf(" ") + 1)).ToChar());
            z = atof(vertex.SubString(vertex.IndexOf(" ", vertex.IndexOf(" ") + 1),
                                      vertex.IndexOf(" ", vertex.IndexOf(" ", vertex.IndexOf(" ") + 1) + 1)).ToChar());

            blue = atof(vertex.SubString(vertex.IndexOf(" ", vertex.IndexOf(" ", vertex.IndexOf(" ") + 1) + 1),
                                        vertex.IndexOf(" ", vertex.IndexOf(" ", vertex.IndexOf(" ", vertex.IndexOf(" ") + 1) + 1) + 1)));
//            green = atof(vertex.SubString(vertex.IndexOf(" ", vertex.IndexOf(" ", vertex.IndexOf(" ")) + 1,
//                                          vertex.IndexOf(" ", vertex.IndexOf(" ") + 1)).ToChar());

            if (blue > 0.5f)
            {
                green = 0.0f;
            }
            else
            {
                green = 1.0f;
            }

            vertices.Add(IDrawable::Vertex(glm::vec3(x, y, z), glm::vec4(0.0f, green, blue, 1.0f)));

            if (firstPoint == true)
            {
                firstPoint = false;
            }
            else
            {
                vertices.Add(IDrawable::Vertex(glm::vec3(x, y, z), glm::vec4(0.0f, green, blue, 1.0f)));
            }
        }
    }

    fclose(dataFile);

    shaders.Insert("data/simple.vert", VERTEX_SHADER);
    shaders.Insert("data/simple.frag", FRAGMENT_SHADER);

    Array<ITexture*> textures = Array<ITexture*>(); // Empty array

    IDrawable* lines = renderer->CreateDrawable(vertices, indices, shaders, textures, DRAW_LINES);

    return lines;
}

double f(const double x)
{
    return (x*x*x) - (6*x*x) + (11*x) - 6;
}

double df(double x)
{
    return (3*x*x) - (12*x) + 11;
}

std::pair<double, int> newton(double x0)
{
    int iter = 0;
    double fx = f(x0);
    double x = x0;

    while (std::abs(fx) > 0.01)
    {
        x = x - fx/df(x);
        fx = f(x);
        iter++;
    }

    return std::pair<double, int>(x, iter);
}

void oppgave1::Init()
{
    // 1. Velg en egen funksjon f(x) og en passende definisjonsmengde D_f = [a, b].
    // f(x) = x3 − 6x2 + 11x − 6
    d_f = Df(-1000, 1000);

    // 2. Velg antall intervaller n slik at du får n + 1 punkter x0,x1,...,xn og oppløsning h = ∆x = (b−a) / n
    n = 10000;
    h = (d_f.b - d_f.a) / n;

    // 3. Regn ut funksjonsverdier f(x_i) i hvert punkt.
    // Regn også ut f'(x) eller Newton's diff􏰁erenskvotient i hvert punkt.
    double x = d_f.a;

    float green, red;

    std::vector<Vertex> vertices;

    for (unsigned int i = 0; i < n + 1; i++)
    {
        // 4. Bestem en farge for hvert verteks slik at grafen får en farge (for eksempel grønn) når funksjonen er
        // stigende, og en annen farge (for eksempel rød) når funksjonen er avtakende.
        if (df(x) > 0.0)
        {
            green = 1.0;
            red = 0.0;
        }
        else
        {
            green = 0.0;
            red = 1.0;
        }

        // 5. Beregn funksjonsverdi og skriv ut verteksdata for hvert punkt på en teksfil.
        // På første linje i filen skal antall punkter stå.
        // Deretter følger verteksdata for hvert punkt linje for linje.
        vertices.push_back(Vertex(x, f(x), 0.0f, red, green, 0.0f));

        x += h;
    }

    // Write file
    dataFile = fopen("data.txt", "w+");

    fprintf(dataFile, "%s%zu%s", "#", vertices.size(), "\n");

    for(const Vertex& v : vertices)
    {
        fprintf(dataFile, "%f %f %f %f %f %f%s", v.x, v.y, v.z, v.r, v.g, v.b, "\n");
    }

    fclose(dataFile);

    drawable = LoadFromFile("data.txt");
}

void oppgave1::Update()
{
    if (input.Pressed(input.Key.RIGHT))
    {
        Application::NextScene();
    }

    renderer->Draw(drawable);
}
