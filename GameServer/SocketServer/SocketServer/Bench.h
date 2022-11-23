#pragma once
#include "ClientSession.h"
#include "Champion.h"

class Bench
{
    map<int, sptr<Champion>> benchMap;

public:
    Bench();

    void Locate(int benchIndex, sptr<Champion> champ);
    void Remove(int benchIndex);
    int GetEmptyBenchIndex();
};
