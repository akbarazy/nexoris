#pragma once
#include <raylib.h>
#include <vector>

class Map
{
private:
    Rectangle area;
    std::vector<Rectangle> objects;

public:
    Map();
    void Draw();
    Rectangle GetArea() const { return area; }
    const std::vector<Rectangle>& GetObjects() const { return objects; }
};