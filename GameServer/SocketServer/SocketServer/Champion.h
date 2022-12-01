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
    void Update(float deltaTime); //Champion Ŭ�������� update�ϱ⿣ �ʵ����͵� �ٸ� champ�����͵� ����..
    void SetBaseStat(ChampStatData statData);


public:
public:
    TransformController transform;
    StatController stat;
    StateController state;
    SkillController skill;
    OperationController operation;
};
