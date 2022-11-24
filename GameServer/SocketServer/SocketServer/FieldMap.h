#pragma once
#include "Vector3.h"

class Hexagon {
private:
    Vector3 position;

public:
    void SetPosition(Vector3 p_position) {
        position = p_position;
    }
};

class FieldMap {

public:
    FieldMap();
    map<int, sptr<Hexagon>> mapData;
    int rowCount = 8;
    int hexagonCountInRow = 8;
    int edgeLength = 8;

    float GetTriangleHeight();
};
