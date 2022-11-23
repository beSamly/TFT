#pragma once
#include "ClientSession.h"
#include "Champion.h"
#include "ShopProbability.h"

class InGamePlayer
{
public:
    InGamePlayer();
    sptr<ClientSession> client;

    ShopProbability shopProb;
    map<int, ChampData> champShop;
    map<int, sptr<Champion>> bench;
    map<int, sptr<Champion>> field;
};
