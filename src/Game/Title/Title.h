#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"
#include"Class.h"
#include"ScoreManager.h"

class Title
{
private:
	static GHandle backImage;
private:
	ScoreManager* scoreManager;

	bool stateEndFlag;
	bool pushStartFlag;
	int timer;
	int endTimer;
	int darkAlpha;
public:
	static void Load();
public:
	Title(ScoreManager* scoreManager);
	~Title();
	void Update();
	void Draw();
	bool GetStateEndFlag()const { return stateEndFlag; }
};