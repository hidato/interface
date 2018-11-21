#include "types.h"
#include <QDebug>

GridMap::GridMap(int width, int height) : width(width), height(height)
{
    size=width*height;
    v = new std::vector<int>(size, 1);
}

GridMap::~GridMap()
{
    delete(v);
}

int &GridMap::at(int a, int b)
{
    const unsigned long i = width*a + b;
    return v->at(i);
}

