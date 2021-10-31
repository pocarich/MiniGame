#pragma once

#include"Define.h"

class Time
{
	static int preTime;
	static int deltaTime;
public:
	static void Init();
	static void UpdateTime();
	static const double GetDeltaTime() { return deltaTime / 1000.0; }
};