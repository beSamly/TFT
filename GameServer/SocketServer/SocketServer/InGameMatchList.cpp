#include "pch.h"
#include "InGameMatchList.h"

InGameMatchList::InGameMatchList() {}

void InGameMatchList::Update(float deltaTime)
{
    for (sptr<InGameMatch>& match : matchList) {
        match->Update(deltaTime);
    }
}

