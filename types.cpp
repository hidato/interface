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

int &GridMap::at(int row, int column)
{
    const unsigned long i = width*row + column;
    return v->at(i);
}

int &GridMap::at(int index)
{
    return v->at(index);
}

