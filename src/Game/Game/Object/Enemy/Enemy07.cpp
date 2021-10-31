#include"../header/Enemy07.h"
#include"../header/Time.h"
#include"../header/Environment.h"
#include"../header/Enemy08.h"
#include"../header/SEMgr.h"

Enemy07::Enemy07(list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy07)
{
	timer = 0.0;
	attackTimer = 0.0;
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
}

Enemy07::~Enemy07()
{

}

void Enemy07::Move()
{
	if (timer < 3.0)
	{
		offsetPos += Vector2<double>(0.0, 200.0) / 3.0*Time::GetDeltaTime();
	}
	else if(timer<12.0)
	{
		attackTimer += Time::GetDeltaTime();
		if (attackTimer > 0.3)
		{
			SEMgr::UpdateFlag(5);
			attackTimer = 0.0;
			enemyList.push_back(make_shared<Enemy08>(enemyList, Vector2<double>(100 + (Define::WINDOW_WIDTH - 200)*GetRand(100) / 100.0, offsetPos.y + Environment::GetCameraHeight() - 200.0), M_PI / 2 - M_PI / 12 + M_PI / 6 * GetRand(100) / 100.0));
		}
	}
	else
	{
		offsetPos += Vector2<double>(0.0, -200.0)*Time::GetDeltaTime();
	}

	timer += Time::GetDeltaTime();

	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}