#include "pch.h"
#include "FieldMap.h"

FieldMap::FieldMap() {
    float triangleHeight = GetTriangleHeight();
    float hexagoneHeight = triangleHeight * 2;
    float halfTriangleHeight = triangleHeight / 2;

    for (int i = 1; i <= rowCount; i++) {

        bool isOddRow = (i % 2) == 1;

        float zOffset = (hexagoneHeight * (i - 1)) + halfTriangleHeight;

        for (int j = 1; j <= hexagonCountInRow; j++) {

            float xOffset = 0 + (isOddRow ? halfTriangleHeight : 0);
            xOffset += (hexagoneHeight * (j - 1)) + halfTriangleHeight;

            sptr<Hexagon> node = make_shared<Hexagon>();
            node->SetPosition(Vector3(xOffset, 0, zOffset));
            mapData.emplace((i * 10) + j, node);
        }
    }
}

float FieldMap::GetTriangleHeight()
{
    return (sqrt(3) * edgeLength) / 2;
}
