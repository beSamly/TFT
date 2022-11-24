#pragma once
#include "Vector3.h"

class Hexagon {
private:
    Vector3 position;

public:
    map<int, sptr<Hexagon>> adjacentNode;
    void SetPosition(Vector3 p_pos) { position = p_pos; }
};

class FieldMap
{
public:
    FieldMap();
    map<int, sptr<Hexagon>> mapData;

private:
    int edgeLength = 10;
    int rowCount = 8;
    int hexagonCountInRow = 8;

private:
    float GetTriangleHeight() {
        float height = (sqrt(3) * edgeLength) / 2;
        return height;
    }
};
