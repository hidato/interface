#ifndef TYPES_H
#define TYPES_H

#include <vector>


class GridMap  {
public:
    int width, height, size;
    std::vector<int> *v;

    GridMap(int width, int height);
    ~GridMap();

    int& at(int row, int column);
    int& at(int index);
};

#endif // TYPES_H
