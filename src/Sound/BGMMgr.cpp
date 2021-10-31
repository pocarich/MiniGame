#include"../header/BGMMgr.h"
#include"../header/Function.h"

MHandle BGMMgr::BGM[1];
bool BGMMgr::BGMStartFlag[1];
bool BGMMgr::BGMStopFlag[1];

void BGMMgr::Load()
{
	for (int i = 0; i < 1; i++)
	{
		stringstream filePath;
		filePath << "data/bgm/bgm" << Function::NumToStringFillZero(i, 2) << ".mp3";

		BGM[i] = LoadSoundMem(filePath.str().c_str());

		assert(BGM[i] != 0 && "BGMMgr::Load()‚É‚ÄBGM‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
	}

	for (int i = 0; i < 1; i++)
	{
		BGMStartFlag[i] = false;
		BGMStopFlag[i] = false;
	}
}

void BGMMgr::Play()
{
	for (int i = 0; i < 1; i++)
	{
		if (BGMStartFlag[i])
		{
			BGMStartFlag[i] = false;
			PlaySoundMem(BGM[i], DX_PLAYTYPE_LOOP);
		}
		if (BGMStopFlag[i])
		{
			BGMStopFlag[i] = false;
			StopSoundMem(BGM[i]);
		}
	}
}

void BGMMgr::UpdateStartFlag(int num)
{
	BGMStartFlag[num] = true;
}

void BGMMgr::UpdateStopFlag(int num)
{
	BGMStopFlag[num] = true;
}