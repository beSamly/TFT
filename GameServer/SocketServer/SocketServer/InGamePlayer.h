#pragma once
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
    sptr<ClientSession> client;

    ShopProbability shopProb;
    ChampShop champShop;
    Field field;
    Bench bench;
};
