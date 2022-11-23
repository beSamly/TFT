#pragma once
#include "ClientSession.h"
#include "Champion.h"

class Field
{
private:
    map<int, sptr<Champion>> fieldMap;

public:
    Field();
    void Locate(int fieldIndex, sptr<Champion> champ);
    void Remove(int fieldIndex);
};
