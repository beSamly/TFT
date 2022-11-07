#pragma once
#include "ITriggerCondition.h"

class TCNone : public ITriggerCondition
{

public:
	bool IsTriggered() override;

};

