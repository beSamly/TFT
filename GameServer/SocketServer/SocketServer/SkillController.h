#pragma once
#include "Vector3.h"

class SkillController
{
public:
    SkillController() {};
    void Update(float deltaTime);
    bool IsUsingSkill();
    bool CanUseSkill();
private:
    //BaseSkill
    //vector<Skill>
};
