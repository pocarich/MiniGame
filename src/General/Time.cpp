#include"../header/Time.h"

int Time::preTime;
int Time::deltaTime;

void Time::Init()
{
	
}

void Time::UpdateTime()
{
	if (preTime != 0)
	{
		deltaTime = GetNowCount() - preTime;
	}
	preTime = GetNowCount();
}