#pragma once
#include "Vector3.h"
#include "Champion.h"

class Hexagon {
private:
    Vector3 position;
    sptr<Champion> champion = nullptr;

public:
    void SetPosition(Vector3 p_position) {
        position = p_position;
    }
    void SetChampion(sptr<Champion> p_champion) { champion = p_champion; }
};

class FieldMap {

public:
    FieldMap();
    void LocateChampion(int fieldUid, sptr<Champion> champion);

private:
    map<int, sptr<Hexagon>> mapData;
    int rowCount = 8;
    int hexagonCountInRow = 8;
    int edgeLength = 8;
    float GetTriangleHeight();
};
