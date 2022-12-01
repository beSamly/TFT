#pragma once
#include "TransformController.h"
#include "StatController.h"
#include "SkillController.h"
#include "OperationController.h"
#include "StateController.h"

class Champion
{
public:
    Champion() {};
    int star;
    int uid;
    void Update(float deltaTime); //Champion 클래스에서 update하기엔 맵데이터도 다른 champ데이터도 없다..
    void SetBaseStat(ChampStatData statData);


public:
public:
    TransformController transform;
    StatController stat;
    StateController state;
    SkillController skill;
    OperationController operation;
};
