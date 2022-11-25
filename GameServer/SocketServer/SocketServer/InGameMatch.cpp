#include "pch.h"
#include "InGameMatch.h"
#include "Field.h"

InGameMatch::InGameMatch() {}

void InGameMatch::InitMatch(Field& fieldA, Field& fieldB)
{
    // TODO 일단 PlayerA 의 챔피언은 fieldUid 그대로 옮긴다.
    for (const auto& [fieldUid, champion] : fieldA.GetFieldData()) {
        fieldMap.LocateChampion(fieldUid, champion);
        aChampions.push_back(champion);
    };

    // PlayerB 의 챔피언은 fieldUid를 flip 한 뒤 옮긴다.
    for (const auto& [fieldUid, champion] : fieldB.GetFieldData()) {
        int rowNumber = fieldUid / 10;
        int columnNumber = fieldUid % (rowNumber * 10);

        int rn = 9 - rowNumber;
        int cn = 9 - columnNumber;

        int targetFieldUid = (rn * 10) + cn;

        fieldMap.LocateChampion(targetFieldUid, champion);
        bChampions.push_back(champion);
    };
}

void InGameMatch::Update(float deltaTime)
{
    //움직이고 있니? 계속 움직여라

    // 스킬 사용 가능하니?
        // 가능하다면 범위에 적 존재하니?
        // 범위에 적 없다면 움직여


    //기본 공격 사용 가능하니?
        //범위에 적 있니?
        //범위에 적 없으면 움직여

}

