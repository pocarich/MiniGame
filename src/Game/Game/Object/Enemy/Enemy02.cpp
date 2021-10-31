#include"../header/Enemy02.h"
#include"../header/Time.h"
#include"../header/Environment.h"

Enemy02::Enemy02(const Player* player,list<EnemyPtr>& enemyList,int direction) :Enemy(enemyList,Vector2<double>(0.0,0.0),EnemyType::Enemy02),player(player),direction(direction)
{
	timer = 0.0;
	counter = 0;
	nowDirection = 0;

	switch (direction)
	{
	case 0:
		offsetPos = Vector2<double>(-100.0, -100.0);
		break;
	case 1:
		offsetPos = Vector2<double>(Define::WINDOW_WIDTH + 100, -100.0);
		break;
	}
}

Enemy02::~Enemy02()
{

}

void Enemy02::Move()
{
	if (counter == 0 || (timer > 2&&counter<4))
	{
		prePos = offsetPos;

		if (counter == 0)
		{
			switch (direction)
			{
			case 0:
				nextPos = Vector2<double>(100.0, 100.0);
				break;
			case 1:
				nextPos = Vector2<double>(Define::WINDOW_WIDTH - 100, 100.0);
				break;
			}
		}
		else
		{
			nextPos = player->GetPosition();
		}
		timer = 0.0;
		counter++;
	}

	if (counter < 4)
	{
		if (timer < 1.0)
		{
			Vector2<double> tempPos = offsetPos;
			offsetPos += (nextPos - prePos) / 1.0*Time::GetDeltaTime();
			nowDirection = (offsetPos - tempPos).x>0.0?1:0;
		}
	}
	else
	{
		Vector2<double> tempPos = offsetPos;
		offsetPos += Vector2<double>(-100 + 200 * direction, -500.0*timer)*Time::GetDeltaTime();
		nowDirection = (offsetPos - tempPos).x>0.0?1:0;
	}

	timer += Time::GetDeltaTime();

	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());

}

void Enemy02::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, 0.0, image[(int)type], TRUE, nowDirection == 1);
}
