#include "pch.h"
#include "InGameMatch.h"
#include "Field.h"

InGameMatch::InGameMatch() {}

void InGameMatch::InitMatch(Field& fieldA, Field& fieldB)
{
    // TODO �ϴ� PlayerA �� è�Ǿ��� fieldUid �״�� �ű��.
    for (const auto& [fieldUid, champion] : fieldA.GetFieldData()) {
        fieldMap.LocateChampion(fieldUid, champion);
        aChampions.push_back(champion);
    };

    // PlayerB �� è�Ǿ��� fieldUid�� flip �� �� �ű��.
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
    //�����̰� �ִ�? ��� ��������

    // ��ų ��� �����ϴ�?
        // �����ϴٸ� ������ �� �����ϴ�?
        // ������ �� ���ٸ� ������


    //�⺻ ���� ��� �����ϴ�?
        //������ �� �ִ�?
        //������ �� ������ ������

}

