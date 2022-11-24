#pragma once
#include "pch.h"
#include "ClientSession.h"
#include "Champion.h"
#include "ShopProbability.h"
#include "ChampShop.h"
#include "Field.h"
#include "Bench.h"

class InGamePlayer
{
public:
    InGamePlayer();
    wptr<ClientSession> client;

    ShopProbability shopProb;
    ChampShop champShop;
    Field field;
    Bench bench;
    int gold;

    bool IsMatched() { return isMatched; }
    void SetMatched(bool value) { isMatched = value; }

private:
    bool isMatched;
};
