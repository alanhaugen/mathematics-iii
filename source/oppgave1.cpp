#include "oppgave1.h"
#include <stdio.h>

//fprintf(dataFile, "%s", "line\n");

// I denne oppgaven skal du lage datapunkter for grafen til en funksjon,
// og punktene skal lagres på en tekstfil med format som forklart på forelesning (Verteksdata linjevis).

oppgave1::oppgave1() :
    d_f(0,0)
{
}

double f(const double x)
{
    return x*x*x-6*x*x+11*x-6;
}

double df(double x)
{
    return 3*x*x-12*x+11;
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
    dataFile = fopen("data.txt", "w+");

    // 1. Velg en egen funksjon f(x) og en passende definisjonsmengde D_f = [a, b].
    // f(x) = x3 − 6x2 + 11x − 6
    d_f = Df(-1000, 1000);

    // 2. Velg antall intervaller n slik at du får n + 1 punkter x0,x1,...,xn og oppløsning h = ∆x = (b−a) / n
    n = 10000;
    h = (d_f.b - d_f.a) / n;

    // 3. Regn ut funksjonsverdier f(x_i) i hvert punkt.
    // Regn også ut f'(x) eller Newton's diff􏰁erenskvotient i hvert punkt.
    fprintf(dataFile, "%s%i%s", "#", n + 1, "\n");

    double x = d_f.a;

    float green, red;

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
        // 5. Beregn funksjonsverdi og skriv ut verteksdata for hvert punkt på en teksfi􏰂l.
        // På første linje i filen skal antall punkter stå.
        // Deretter følger verteksdata for hvert punkt linje for linje.
        fprintf(dataFile, "%f %f %f %f %f%s", x, f(x), red, green, 0.0f, "\n");

        x += h;
    }

    fclose(dataFile);
}

void oppgave1::Update()
{
}
