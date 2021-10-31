
/*   BGMä«óù   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"

class BGMMgr :public Singleton
{
	static MHandle BGM[1];
	static bool BGMStartFlag[1];
	static bool BGMStopFlag[1];
public:
	static void Load();
	static void Play();
	static void UpdateStartFlag(int);
	static void UpdateStopFlag(int);
};
