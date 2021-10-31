#include"../header/GameMgr.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/ScoreManager.h"

GameMgr::GameMgr()
{
	title = nullptr;
	state = GameState::TITLE;
	scoreManager = new ScoreManager();
}

GameMgr::~GameMgr()
{
	if (title != nullptr)
		delete title;
	if (game != nullptr)
		delete game;
	
	delete scoreManager;
}

void GameMgr::Main()
{
	switch (state)
	{
	case GameState::TITLE:	TitleFunc();	break;
	case GameState::GAME:	GameFunc();		break;
	}
}

void GameMgr::TitleFunc()
{
	if (title == nullptr)
	{
		title = new Title(scoreManager);
	}

	title->Update();
	title->Draw();

	if (title->GetStateEndFlag())
	{
		delete title;
		title = nullptr;
		state = GameState::GAME;
	}
}

void GameMgr::GameFunc()
{
	if (game == nullptr)
	{
		game = new Game(scoreManager);
	}
	
	game->Update();
	game->Draw();

	if (game->GetEndFlag())
	{
		ScoreManager::Save();
		delete game;
		game = nullptr;
		state = GameState::TITLE;
	}
}