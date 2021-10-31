#pragma once

#include"Define.h"

class Environment
{
private:
	static double height;
public:
	static void UpdateHeight(double deltaHeight) { height += deltaHeight; }
	static void ResetHeight() { height = 0.0; }
	static double GetHeight() { return -height; }
	static double GetCameraHeight() { return height; }
};