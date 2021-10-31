#include"../header/Enemy10.h"
#include"../header/Time.h"
#include"../header/Environment.h"
#include"../header/Enemy11.h"
#include"../header/SEMgr.h"

Enemy10::Enemy10(const Player* player,list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy10),player(player)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
	timer = 0.0;
	attackTimer[0] = 0.0;
	attackTimer[1] = 0.0;
	attackAngle[0] = 10000.0;
	attackAngle[1] = 10000.0;
}

Enemy10::~Enemy10()
{

}

void Enemy10::Move()
{
	if (timer < 3.0)
	{
		offsetPos += Vector2<double>(0.0, 100.0 - (Define::WINDOW_HEIGHT + 200)) / 3.0*Time::GetDeltaTime();
	}
	else if(timer<8.0)
	{
		attackTimer[0] += Time::GetDeltaTime();
		attackTimer[1] += Time::GetDeltaTime();

		if (attackTimer[0] > 2.0)
		{
			attackTimer[0] = 0.0;
			attackAngle[0] = atan2(player->GetPosition().y - (offsetPos.y+15), player->GetPosition().x - (offsetPos.x+50.0));
			attackAngle[1] = atan2(player->GetPosition().y - (offsetPos.y+15), player->GetPosition().x - (offsetPos.x-50.0));
		}

		if (attackTimer[0] < 1.0&&attackTimer[1]>0.1)
		{
			SEMgr::UpdateFlag(5);
			attackTimer[1] = 0.0;
			if (attackAngle[0] < 1000.0)
			{
				for (int i = 0; i < 3; i++)
				{
					enemyList.push_back(make_shared<Enemy11>(enemyList, Vector2<double>(offsetPos.x + 50.0, offsetPos.y + 15.0 + Environment::GetCameraHeight()), attackAngle[0] - M_PI / 4 + M_PI / 4 * i));
					enemyList.push_back(make_shared<Enemy11>(enemyList, Vector2<double>(offsetPos.x - 50.0, offsetPos.y + 15.0 + Environment::GetCameraHeight()), attackAngle[1] - M_PI / 4 + M_PI / 4 * i));
				}
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