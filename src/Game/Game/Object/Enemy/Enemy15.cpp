#include"../header/Enemy15.h"
#include"../header/Time.h"
#include"../header/Environment.h"
#include"../header/Enemy16.h"
#include"../header/Enemy17.h"
#include"../header/Enemy18.h"
#include"../header/SEMgr.h"

Enemy15::Enemy15(const Player* player,list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy15),player(player)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
	timer = 0.0;
	attackTimer = 0.0;
	startTimer = 0.0;
	state = GetRand(100) % 3;
	sw = 0;
}

Enemy15::~Enemy15()
{

}

void Enemy15::Move()
{
	if (startTimer < 3.0)
	{
		offsetPos += Vector2<double>(0.0, 300.0) / 3.0*Time::GetDeltaTime();
	}
	else
	{
		switch (state)
		{
		case 0:
			if (timer < 3.0)
			{
				if (attackTimer > 0.2)
				{
					SEMgr::UpdateFlag(5);
					attackTimer = 0.0;
					double randAngle = atan2(player->GetPosition().y - offsetPos.y, player->GetPosition().x - offsetPos.x);
					for (int i = 0; i < 14; i++)
					{
						enemyList.push_back(make_shared<Enemy16>(enemyList, offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight()), randAngle + 2 * M_PI / 14 * i));
					}
				}
			}
			else if(5.0<timer)
			{
				timer = 0.0;
				attackTimer = 0.0;
				state = GetRand(100) % 3;
			}
			break;
		case 1:
			if (timer < 7.0)
			{
				if (attackTimer > 0.5)
				{
					SEMgr::UpdateFlag(5);
					attackTimer = 0.0;
					double randAngle = 2 * M_PI / 32 * sw;
					sw^= 1;
					for (int i = 0; i < 20; i++)
					{
						enemyList.push_back(make_shared<Enemy17>(enemyList, offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight()), randAngle + 2 * M_PI / 20 * i));
					}
				}
			}
			else if(9.0<timer)
			{
				timer = 0.0;
				attackTimer = 0.0;
				state = GetRand(100) % 3;
			}
			break;
		case 2:
			if (timer < 3.1)
			{
				if (attackTimer > 0.5)
				{
					attackTimer = 0.0;
					int rand = -1 + GetRand(100) % 3;
					for (int i = 0; i < 11; i++)
					{
						if (5 - i == rand)
						{
							continue;
						}
						enemyList.push_back(make_shared<Enemy18>(enemyList, Vector2<double>(100.0*i, Environment::GetCameraHeight())));
					}
				}
			}
			else if (8.0<timer)
			{
				timer = 0.0;
				attackTimer = 0.0;
				state = GetRand(100) % 3;
			}
			break;
		}
		timer += Time::GetDeltaTime();
	}

	attackTimer += Time::GetDeltaTime();
	startTimer += Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}