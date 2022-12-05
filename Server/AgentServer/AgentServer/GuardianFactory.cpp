#include "pch.h"
#include "GuardianFactory.h"

GuardianFactory::GuardianFactory()
{
	Init();
}

void GuardianFactory::Init()
{
}

GuardianFactory* GuardianFactory::GetInstance()
{
	static GuardianFactory* instance = new GuardianFactory();
	return instance;
}
