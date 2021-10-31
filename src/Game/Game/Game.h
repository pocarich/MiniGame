#pragma once

#include"Define.h"
#include"ScoreManager.h"
#include"Player.h"

class Game
{
private:
	enum struct GameState
	{
		START,
		PLAY,
		END,
		GAMEOVER,
		SIZE
	};
private:
	static array<GHandle, 7> backImage;
private:
	Player* player;
	list<BalloonPtr> balloonList;
	list<ItemPtr> itemList;
	list<EnemyPtr> enemyList;
	list<EffectPtr> effectList;
	ScoreManager* scoreManager;

	GameState state;
	array<float, (int)GameState::SIZE> timer;
	double alphaTimer;
	bool fadeOutFlag;
	int endState;
	double endDrawOffset;
	double startDispTimer;
	bool endFlag;
	double gameOverTimer;

	array<int, 7> backImageHeight;
	int objectSpawnIndex;
public:
	static void Load();
private:
	void UpdateStart();
	void UpdatePlay();
	void UpdatePlayTimer();
	void UpdateEnd();
	void UpdateGameOver();
	void SpawnObject();
	void DeleteObject();
	void DetectItem();
public:
	Game(ScoreManager* scoreManager);
	~Game();
	void Update();
	void Draw();
	bool GetEndFlag()const { return endFlag; }
};