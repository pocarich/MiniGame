#include"../header/Enemy18.h"
#include"../header/Time.h"
#include"../header/Environment.h"
#include"../header/SEMgr.h"

Enemy18::Enemy18(list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy18)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
	timer = 0.0;
	ySpeed = 300.0;
	seFlag = false;
	SEMgr::UpdateFlag(5);
}

Enemy18::~Enemy18()
{

}

void Enemy18::Move()
{
	if (timer < 1.0)
	{
		ySpeed -= 300.0*Time::GetDeltaTime();
		offsetPos += Vector2<double>(0.0, ySpeed)*Time::GetDeltaTime();
	}
	else if (3.0 < timer)
	{
		if (!seFlag)
		{
			SEMgr::UpdateFlag(5);
			seFlag = true;
		}

		offsetPos += Vector2<double>(0.0, 3000.0)*Time::GetDeltaTime();
	}

	timer += Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}