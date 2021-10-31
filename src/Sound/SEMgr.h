
/*   SEä«óù   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"

class SEMgr :public Singleton
{
	static const int SENum = 8;
	static MHandle SEList[SENum];
	static bool SEFlag[SENum];
public:
	static void Load();
	static void Play();
	static void UpdateFlag(int);
};