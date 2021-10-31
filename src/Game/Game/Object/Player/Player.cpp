#include"../header/Player.h"
#include"../header/Time.h"
#include"../header/Environment.h"
#include"../header/KeyBoard.h"
#include"../header/ColorMgr.h"
#include"../header/Balloon.h"
#include"../header/Item.h"
#include"../header/Mouse.h"
#include"../header/Enemy.h"
#include"../header/BalloonEffect.h"
#include"../header/SEMgr.h"

GHandle Player::image;
GHandle Player::balloonImage[5];

const double Player::range = 30.0;

void Player::Load()
{
	image = LoadGraph("data/graph/character/player.png");
	for (int i = 0; i < 5; i++)
	{
		stringstream ss;
		ss << "data/graph/character/balloon" << i << ".png";
		balloonImage[i] = LoadGraph(ss.str().c_str());
	}
}

Player::Player(list<BalloonPtr>& balloonList, list<ItemPtr>& itemList, list<EnemyPtr>& enemyList, list<EffectPtr>& effectList):balloonList(balloonList),itemList(itemList),enemyList(enemyList),effectList(effectList)
{
	position = Vector2<double>(Define::WINDOW_WIDTH / 2.0, Define::WINDOW_HEIGHT - 100.0);
	detectingItem = -1;
	heldBalloonList.push_back(0);
	attackedTimer = 0.0;
}

Player::~Player()
{

}

void Player::Update()
{
	UpdateHeight();
	Move();
	DetectCollision();
}

void Player::UpdateHeight()
{
	if (heldBalloonList.size() == 0)
	{
		return;
	}
	Environment::UpdateHeight(-(Define::DEFAULT_SPEED + Define::ADD_SPEED*(int)heldBalloonList.size())*Time::GetDeltaTime());
}

void Player::Move()
{
	if (heldBalloonList.size() != 0)
	{
		position = Mouse::GetMousePos();
		position.x = min(max(50.0, position.x), Define::WINDOW_WIDTH - 50.0);
		position.y = min(max(50.0, position.y), Define::WINDOW_HEIGHT - 50.0);
	}
	else
	{
		position += Vector2<double>(0.0, 400.0)*Time::GetDeltaTime();
	}
}

void Player::AddBalloon(int type)
{
	if (heldBalloonList.size() == 0||heldBalloonList.size()>=Define::MAX_HELD_BALLOON_NUM)
	{
		return;
	}

	SEMgr::UpdateFlag(2);
	heldBalloonList.push_back(type);
}

void Player::DetectCollision()
{
	if (heldBalloonList.size() == 0)
	{
		return;
	}

	attackedTimer -= Time::GetDeltaTime();
	attackedTimer = max(0.0, attackedTimer);

	for (auto& obj : balloonList)
	{
		double r_sum = range + obj->GetRange();
		if ((position - (obj->GetPosition()-Vector2<double>(0.0,Environment::GetCameraHeight()))).length2() < r_sum*r_sum)
		{
			AddBalloon(obj->GetBalloonColor());
			obj->Collided();
		}
	}

	for (auto& obj : itemList)
	{
		double r_sum = range + obj->GetRange();
		if ((position - (obj->GetPosition() - Vector2<double>(0.0, Environment::GetCameraHeight()))).length2() < r_sum*r_sum)
		{
			DetectItem();
			obj->Collided();
		}
	}

	for (auto& obj : enemyList)
	{
		double r_sum = range + obj->GetRange();
		if ((position - (obj->GetPosition() - Vector2<double>(0.0, Environment::GetCameraHeight()))).length2() < r_sum*r_sum)
		{
			CollideEnemy();
			obj->Collided();
		}
	}
}

void Player::DetectItem()
{
	SEMgr::UpdateFlag(3);
	detectingItem = 0;
}

void Player::CollideEnemy()
{
	if (heldBalloonList.size() == 0||attackedTimer>0.001)
	{
		return;
	}

	SEMgr::UpdateFlag(4);
	if (heldBalloonList.size() > 1)
	{
		attackedTimer = Define::ATTACKED_TIME;
	}
	effectList.push_back(make_shared<BalloonEffect>(position, heldBalloonList.back()));
	heldBalloonList.pop_back();
}

void Player::Draw()
{
	if ((int)(attackedTimer*20.0) % 2 == 1)return;

	for (int i = 0; i != heldBalloonList.size(); i++)
	{
		double tempAngle = -M_PI / 2 - M_PI / 12 * ((int)heldBalloonList.size() - 1) / 2 + M_PI / 12 * i;
		Vector2<double> tempPos = position + Vector2<double>(cos(tempAngle), sin(tempAngle))*100.0;
		DrawRotaGraphF((float)tempPos.x, (float)tempPos.y, 1.0, tempAngle + M_PI / 2, balloonImage[heldBalloonList[i]], TRUE);
	}
	DrawRotaGraphF((float)position.x, (float)position.y, 1.0, 0.0, image, TRUE);
}