#include"../header/Game.h"
#include"../header/Environment.h"
#include"../header/Time.h"
#include"../header/Function.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/Balloon.h"
#include"../header/ObjectSpawnInfoList.h"
#include"../header/Item.h"
#include"../header/Mouse.h"
#include"../header/KeyBoard.h"
#include"../header/Enemy.h"
#include"../header/ScoreManager.h"
#include"../header/Effect.h"
#include"../header/SEMgr.h"

#include"../header/Enemy00.h"
#include"../header/Enemy01.h"
#include"../header/Enemy02.h"
#include"../header/Enemy03.h"
#include"../header/Enemy04.h"
#include"../header/Enemy05.h"
#include"../header/Enemy06.h"
#include"../header/Enemy07.h"
#include"../header/Enemy08.h"
#include"../header/Enemy09.h"
#include"../header/Enemy10.h"
#include"../header/Enemy11.h"
#include"../header/Enemy12.h"
#include"../header/Enemy13.h"
#include"../header/Enemy14.h"
#include"../header/Enemy15.h"
#include"../header/Enemy16.h"
#include"../header/Enemy17.h"
#include"../header/Enemy18.h"
#include"../header/Enemy19.h"
#include"../header/Enemy20.h"

array<GHandle, 7> Game::backImage;

void Game::Load()
{
	for (int i = 0; i < 7; i++)
	{
		stringstream ss;
		ss << "data/graph/common/map" << i << ".jpg";
		backImage[i] = LoadGraph(ss.str().c_str());
	}
}

Game::Game(ScoreManager* scoreManager):scoreManager(scoreManager)
{
	player = new Player(balloonList,itemList,enemyList,effectList);

	state = GameState::START;
	endFlag = false;
	fadeOutFlag = false;
	objectSpawnIndex = 0;
	endState = 0;
	endDrawOffset = 0.0;
	alphaTimer = 0.0;
	gameOverTimer = 0.0;
	startDispTimer = 0.0;

	for (auto& n : timer)n = 0.0;

	for (int i = 0; i != backImage.size(); i++)
	{
		int w, h;
		GetGraphSize(backImage[i], &w, &h);
		backImageHeight[i] = h;
	}

	Environment::ResetHeight();
}

Game::~Game()
{
	delete player;
}

void Game::Update()
{
	switch (state)
	{
	case GameState::START:
		UpdateStart();
		break;
	case GameState::PLAY:
		UpdatePlay();
		break;
	case GameState::END:
		UpdateEnd();
		break;
	case GameState::GAMEOVER:
		UpdateGameOver();
		break;
	}
}

void Game::UpdateStart()
{
	timer[(int)GameState::START] += Time::GetDeltaTime();
	if (timer[(int)GameState::START] > 3.0)
	{
		SEMgr::UpdateFlag(1);
		state = GameState::PLAY;
	}
}

void Game::UpdatePlay()
{
	SpawnObject();
	DeleteObject();
	DetectItem();

	player->Update();
	if (player->GetBalloonNum() > 0)
	{
		for (auto& obj : balloonList)obj->Update();
		for (auto& obj : itemList)obj->Update();
		for (auto& obj : enemyList)obj->Update();
	}
	for (auto& obj : effectList)obj->Update();

	UpdatePlayTimer();

	//printfDx("%d\n", enemyList.size());
}

void Game::UpdatePlayTimer()
{
	startDispTimer += Time::GetDeltaTime();
	if (player->GetBalloonNum() != 0)
	{
		timer[(int)GameState::PLAY] += Time::GetDeltaTime();
		if (timer[(int)GameState::PLAY] > Define::LIMIT_TIME)
		{
			SEMgr::UpdateFlag(1);
			ScoreManager::UpdateScore((int)Environment::GetHeight());
			state = GameState::END;
		}
	}
	if (player->GetBalloonNum() == 0)
	{
		gameOverTimer += Time::GetDeltaTime();
		if (gameOverTimer > 3.0)
		{
			SEMgr::UpdateFlag(1);
			ScoreManager::UpdateScore((int)Environment::GetHeight());
			state = GameState::END;
		}
	}
}

void Game::SpawnObject()
{
	while (objectSpawnIndex != ObjectSpawnInfoList::GetObjectSpawnInfoList().size() && ObjectSpawnInfoList::GetObjectSpawnInfoList()[objectSpawnIndex].spawnHeight < Environment::GetHeight())
	{
		const ObjectSpawnInfoList::ObjectSpawnInfo& tempOsi = ObjectSpawnInfoList::GetObjectSpawnInfoList()[objectSpawnIndex];
		
		Vector2<double> spawnPos;
		if (tempOsi.option == 0)
		{
			spawnPos = tempOsi.position;
		}
		switch (tempOsi.objectID)
		{
		case ObjectID::BALLOON:
			if (tempOsi.option ==-1)
			{
				spawnPos = Vector2<double>(100 + (Define::WINDOW_WIDTH - 200)*GetRand(100) / 100.0, -tempOsi.spawnHeight - 200.0);
			}
			balloonList.push_back(make_shared<Balloon>(spawnPos));
			break;
		case ObjectID::ITEM:
			if (tempOsi.option == -1)
			{
				spawnPos = Vector2<double>(100 + (Define::WINDOW_WIDTH - 200)*GetRand(100) / 100.0, -tempOsi.spawnHeight - 200.0);
			}
			itemList.push_back(make_shared<Item>(spawnPos));
			break;
		case ObjectID::ENEMY:
			switch ((Enemy::EnemyType)tempOsi.type)
			{
			case Enemy::EnemyType::Enemy00:
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(100 + (Define::WINDOW_WIDTH - 200)*GetRand(100) / 100.0, -tempOsi.spawnHeight - 200.0);
				}
				enemyList.push_back(make_shared<Enemy00>(enemyList, spawnPos));
				break;
			case Enemy::EnemyType::Enemy01: {
				int direction = -1 + 2 * (GetRand(100) % 2);
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(Define::WINDOW_WIDTH / 2 + (-1)*direction*(Define::WINDOW_WIDTH / 2 + 100), -tempOsi.spawnHeight + Define::WINDOW_HEIGHT - 50 - (Define::WINDOW_HEIGHT - 100) * GetRand(100) / 100.0);
				}
				else
				{
					direction = tempOsi.value;
				}
				enemyList.push_back(make_shared<Enemy01>(enemyList, spawnPos, direction));
				break;
			}
			case Enemy::EnemyType::Enemy02: {
				int direction = GetRand(100) % 2;
				if (tempOsi.option != -1)
				{
					direction = tempOsi.value;
				}
				enemyList.push_back(make_shared<Enemy02>(player, enemyList, direction));
				break;
			}
			case Enemy::EnemyType::Enemy03: {
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(100 + (Define::WINDOW_WIDTH - 200)*GetRand(100) / 100.0, -tempOsi.spawnHeight - 200.0);
				}
				enemyList.push_back(make_shared<Enemy03>(player, enemyList, spawnPos));
				break;
			}
			case Enemy::EnemyType::Enemy05:
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(100 + (Define::WINDOW_WIDTH - 200)*GetRand(100) / 100.0, -tempOsi.spawnHeight - 200.0);
				}
				enemyList.push_back(make_shared<Enemy05>(enemyList, spawnPos));
				break;
			case Enemy::EnemyType::Enemy06: {
				int direction = -1 + 2 * (GetRand(100) % 2);
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(Define::WINDOW_WIDTH / 2 + (-1)*direction*(Define::WINDOW_WIDTH + 150 / 2), -tempOsi.spawnHeight + Define::WINDOW_HEIGHT - 100 - (Define::WINDOW_HEIGHT - 200) * GetRand(100) / 100.0);
				}
				else
				{
					direction = tempOsi.value;
				}
				enemyList.push_back(make_shared<Enemy06>(enemyList, spawnPos, direction));
				break;
			}
			case Enemy::EnemyType::Enemy07:
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(Define::WINDOW_WIDTH / 2, -tempOsi.spawnHeight - 200.0);
				}
				enemyList.push_back(make_shared<Enemy07>(enemyList, spawnPos));
				break;
			case Enemy::EnemyType::Enemy09:
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(30 + (Define::WINDOW_WIDTH - 60)*GetRand(100) / 100.0, -tempOsi.spawnHeight - 100.0);
				}
				enemyList.push_back(make_shared<Enemy09>(enemyList, spawnPos, M_PI / 2 - M_PI / 12 + M_PI / 6 * GetRand(100) / 100.0));
				break;
			case Enemy::EnemyType::Enemy10:
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(100 + (Define::WINDOW_WIDTH - 200)*GetRand(100) / 100.0, -tempOsi.spawnHeight + Define::WINDOW_HEIGHT + 200.0);
				}
				enemyList.push_back(make_shared<Enemy10>(player, enemyList, spawnPos));
				break;
			case Enemy::EnemyType::Enemy12: {
				int direction = -1 + 2 * (GetRand(100) % 2);
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(Define::WINDOW_WIDTH / 2 + (-1)*direction*(Define::WINDOW_WIDTH / 2 + 150), -tempOsi.spawnHeight + Define::WINDOW_HEIGHT - 100 - (Define::WINDOW_HEIGHT - 200) * GetRand(100) / 100.0);
				}
				else
				{
					direction = tempOsi.value;
				}
				enemyList.push_back(make_shared<Enemy12>(player,enemyList, spawnPos, direction));
				break;
			}
			case Enemy::EnemyType::Enemy13: {
				int direction = -1 + 2 * (GetRand(100) % 2);
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(Define::WINDOW_WIDTH / 2 + (-1)*direction*(Define::WINDOW_WIDTH / 2 - 150), -tempOsi.spawnHeight - 150.0);
				}
				else
				{
					direction = tempOsi.value;
				}
				enemyList.push_back(make_shared<Enemy13>(enemyList, spawnPos));
				break;
			}
			case Enemy::EnemyType::Enemy15: {
				if (tempOsi.option == -1)
				{
					spawnPos = Vector2<double>(Define::WINDOW_WIDTH / 2, -tempOsi.spawnHeight - 150.0);
				}
				enemyList.push_back(make_shared<Enemy15>(player,enemyList, spawnPos));
				break;
			}
			}
			break;
		}

		objectSpawnIndex++;
	}
}

void Game::DeleteObject()
{
	balloonList.erase(remove_if(balloonList.begin(), balloonList.end(), [&](BalloonPtr& obj) {return obj->GetDeathFlag(); }), balloonList.end());
	itemList.erase(remove_if(itemList.begin(), itemList.end(), [&](ItemPtr& obj) {return obj->GetDeathFlag(); }), itemList.end());
	enemyList.erase(remove_if(enemyList.begin(), enemyList.end(), [&](EnemyPtr& obj) {return obj->GetDeathFlag(); }), enemyList.end());
	effectList.erase(remove_if(effectList.begin(), effectList.end(), [&](EffectPtr& obj) {return obj->GetDeathFlag(); }), effectList.end());
}

void Game::DetectItem()
{
	if (player->GetDetectingItem() != -1)
	{
		timer[(int)GameState::PLAY] = timer[(int)GameState::PLAY] - Define::ADD_TIMER;
		player->ResetDetectingItem();
	}
}

void Game::UpdateEnd()
{
	timer[(int)GameState::END] += Time::GetDeltaTime();
	if (timer[(int)GameState::END] > 3.0)
	{
		if (Mouse::ClickOnce(MOUSE_INPUT_LEFT)&&!fadeOutFlag)
		{
			SEMgr::UpdateFlag(0);
			if (endState == 0)
			{
				endState++;
			}
			else if(endState==1)
			{
				fadeOutFlag = true;
			}
		}
	}
	if (endState == 1)
	{
		endDrawOffset = min(Define::WINDOW_WIDTH, endDrawOffset + Define::WINDOW_WIDTH / 0.5*Time::GetDeltaTime());

	}
	if (fadeOutFlag)
	{
		alphaTimer += Time::GetDeltaTime();
		if (alphaTimer > 3.0)
		{
			endFlag = true;
		}
	}
}

void Game::UpdateGameOver()
{
	timer[(int)GameState::GAMEOVER] += Time::GetDeltaTime();
	if (timer[(int)GameState::GAMEOVER] > 5.0)
	{
		//ScoreUpdate();
		endFlag = true;
	}
}

void Game::Draw()
{
	int th = -backImageHeight[0];
	
	DrawGraphF(0.0f, (float)(th + Define::WINDOW_HEIGHT - Environment::GetCameraHeight()), backImage[0], TRUE);
	th -= backImageHeight[1];
	DrawGraphF(0.0f, (float)(th + Define::WINDOW_HEIGHT - Environment::GetCameraHeight()), backImage[1], TRUE);
	for (int i = 0; i < Define::BACK_SKY_NUM; i++)
	{
		th -= backImageHeight[2];
		DrawGraphF(0.0f, (float)(th + Define::WINDOW_HEIGHT - Environment::GetCameraHeight()), backImage[2], TRUE);
	}
	th -= backImageHeight[3];
	DrawGraphF(0.0f, (float)(th + Define::WINDOW_HEIGHT - Environment::GetCameraHeight()), backImage[3], TRUE);
	for (int i = 0; i < Define::BACK_SPACE_NUM; i++)
	{
		th -= backImageHeight[4];
		DrawGraphF(0.0f, (float)(th + Define::WINDOW_HEIGHT - Environment::GetCameraHeight()), backImage[4], TRUE);
	}
	th -= backImageHeight[5];
	DrawGraphF(0.0f, (float)(th + Define::WINDOW_HEIGHT - Environment::GetCameraHeight()), backImage[5], TRUE);
	for (int i = 0; i < Define::BACK_HEAVEN_NUM; i++)
	{
		th -= backImageHeight[6];
		DrawGraphF(0.0f, (float)(th + Define::WINDOW_HEIGHT - Environment::GetCameraHeight()), backImage[6], TRUE);
	}

	for (auto& obj : effectList)obj->Draw();
	player->Draw();
	for (auto& obj : enemyList)obj->Draw();
	for (auto& obj : balloonList)obj->Draw();
	for (auto& obj : itemList)obj->Draw();

	if (state == GameState::PLAY)
	{
		stringstream ss;
		ss << (int)(Define::LIMIT_TIME+0.9999999 - timer[(int)GameState::PLAY]);
		string countStr = ss.str();

		Function::Alpha(128);
		if ((int)(Define::LIMIT_TIME + 0.9999999 - timer[(int)GameState::PLAY])>3)
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[23], countStr.c_str()), 30.0, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[23], countStr.c_str());
		}
		else
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[23], countStr.c_str()), 30.0, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[23], countStr.c_str());
		}
		Function::Alpha(255);
	}

	if (startDispTimer < 1.0)
	{
		if (timer[(int)GameState::START] < 3.0)
		{
			stringstream ss;
			ss << (int)(3.99999 - timer[(int)GameState::START]);
			string countStr = ss.str();
			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[23], countStr.c_str()), Define::WINDOW_HEIGHT / 2 - 30.0, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[23], countStr.c_str());
		}
		else
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[23], "スタート!!"), Define::WINDOW_HEIGHT / 2 - 30.0, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[23], "スタート!!");
		}
	}

	if (state == GameState::END)
	{
		if (timer[(int)GameState::END] < 2.0)
		{
			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[23], "そこまで!!"), Define::WINDOW_HEIGHT / 2 - 30.0, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[23], "そこまで!!");
		}
		if (3.0 < timer[(int)GameState::END])
		{
			Function::Alpha(128);
			DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
			Function::Alpha(255);

			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[23], "スコア")-endDrawOffset, Define::WINDOW_HEIGHT / 2 - 180.0, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[23], "スコア");
			DrawFormatStringToHandle(Define::WINDOW_WIDTH / 2 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[24], "%05d", (int)Environment::GetHeight()) / 2 - endDrawOffset, Define::WINDOW_HEIGHT / 2, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[24], "%05d", (int)Environment::GetHeight());
			
			Function::Alpha(128 * (1 + sin(2 * M_PI*1.0*timer[(int)GameState::END])));
			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[20], "マウスをひだりクリックしてください") - endDrawOffset, Define::WINDOW_HEIGHT-100, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[20], "マウスをひだりクリックしてください");
			Function::Alpha(255);
			Function::Alpha(128 * (1 + sin(2 * M_PI*1.0*timer[(int)GameState::END])));
			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[20], "マウスをひだりクリックしてください") + Define::WINDOW_WIDTH - endDrawOffset, Define::WINDOW_HEIGHT - 70, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[20], "マウスをひだりクリックしてください");
			Function::Alpha(255);

			DrawFormatStringToHandle(Function::CalcCenterOfString(0, Define::WINDOW_WIDTH, FontMgr::GetFont()[23], "ランキング") + Define::WINDOW_WIDTH - endDrawOffset, 50.0, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[23], "ランキング");

			for (int i = 0; i != ScoreManager::GetSavedScoreList().size(); i++)
			{
				if (i == ScoreManager::GetRank())
				{
					DrawFormatStringToHandle(Define::WINDOW_WIDTH / 2 - 150 + Define::WINDOW_WIDTH - endDrawOffset, 150.0 + 50.0*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[21], "%d位：", i + 1);
					DrawFormatStringToHandle(Define::WINDOW_WIDTH / 2 + 150 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[21], "%05d", (int)Environment::GetHeight()) + Define::WINDOW_WIDTH - endDrawOffset, 150.0 + 50.0*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED], FontMgr::GetFont()[21], "%05d", ScoreManager::GetSavedScoreList()[i]);

				}
				else
				{
					DrawFormatStringToHandle(Define::WINDOW_WIDTH / 2 - 150 + Define::WINDOW_WIDTH - endDrawOffset, 150.0 + 50.0*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[21], "%d位：", i + 1);
					DrawFormatStringToHandle(Define::WINDOW_WIDTH / 2 + 150 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[21], "%05d", (int)Environment::GetHeight()) + Define::WINDOW_WIDTH - endDrawOffset, 150.0 + 50.0*i, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[21], "%05d", ScoreManager::GetSavedScoreList()[i]);
				}
			}
		}
	}

	Function::Alpha(min(255, (int)(255 * alphaTimer / 2.0)));
	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);
	Function::Alpha(255);
}