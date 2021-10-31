#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"
#include"Title.h"
#include"Game.h"
#include"ScoreManager.h"

class GameMgr
{
private:
	enum struct GameState
	{
		TITLE,
		GAME,
		RESULT
	};
private:
	GameState state;
	Title* title;
	Game* game;
	ScoreManager* scoreManager;
private:
	void TitleFunc();
	void GameFunc();
public:
	GameMgr();
	~GameMgr();
	void Main();
};
