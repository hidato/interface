#ifndef TYPES_H
#define TYPES_H

#include <vector>


class GridMap  {
public:
    int width, height, size;
    std::vector<int> *v;

    GridMap(int width, int height);
    ~GridMap();

    int& at(int a, int b);
};

#endif // TYPES_H
