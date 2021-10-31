#include"../header/Enemy13.h"
#include"../header/Time.h"
#include"../header/Enemy14.h"
#include"../header/Environment.h"
#include"../header/SEMgr.h"

Enemy13::Enemy13(list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy13)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
	timer = 0.0;
	attackTimer[0] = 0.0;
	attackTimer[1] = 0.0;
	attackAngle = 100000.0;
	attackState = 0;
}

Enemy13::~Enemy13()
{

}

void Enemy13::Move()
{
	if (timer < 3.0)
	{
		offsetPos += Vector2<double>(0.0, 300.0) / 3.0*Time::GetDeltaTime();
	}
	else if (timer < 12.0)
	{
		attackTimer[0] += Time::GetDeltaTime();
		attackTimer[1] += Time::GetDeltaTime();

		if (attackTimer[0]>3.0)
		{
			attackTimer[0] = 0.0;
			attackAngle = M_PI*GetRand(100) / 100.0;
		}
		if (attackTimer[0]<2.0&&attackTimer[1]>0.5)
		{
			SEMgr::UpdateFlag(5);
			attackTimer[1] = 0.0;
			attackState ^= 1;
			for (int i = 0; i < 16; i++)
			{
				enemyList.push_back(make_shared<Enemy14>(enemyList, offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight()), attackAngle + 2 * M_PI / (16 * 2)*attackState + 2 * M_PI / 16 * i));
			}
		}
	}
	else
	{
		offsetPos += Vector2<double>(0.0, -300.0)*Time::GetDeltaTime();
	}

	timer += Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}