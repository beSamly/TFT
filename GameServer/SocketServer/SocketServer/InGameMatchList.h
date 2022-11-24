#pragma once
#include "InGameMatch.h"

class InGameMatchList
{
public:
    InGameMatchList();
    vector<sptr<InGameMatch>> matchList;

    void AddMatch(sptr<InGameMatch> match) { matchList.push_back(match); };
    bool Reset() { matchList.clear(); };
    void Update(float deltaTime);
};
