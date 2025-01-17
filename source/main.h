#define M_PI 3.141592653589793238462643383279502884L

struct Vertex
{
    float x,y,z,r,g,b;

    Vertex(float x_, float y_, float z_, float r_, float g_, float b_)
    {
        x = x_;
        y = y_;
        z = z_;
        r = r_;
        g = g_;
        b = b_;
    }
};
