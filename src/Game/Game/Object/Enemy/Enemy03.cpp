#include"../header/Enemy03.h"
#include"../header/Time.h"
#include"../header/Environment.h"
#include"../header/Enemy04.h"
#include"../header/SEMgr.h"

Enemy03::Enemy03(const Player* player,list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy03),player(player)
{
	offsetPos = Vector2<double>(position.x, -100.0);
	state = 0;
	direction = 1;
}

Enemy03::~Enemy03()
{

}

void Enemy03::Move()
{
	switch (state)
	{
	case 0:
		offsetPos += Vector2<double>(0.0, 200.0)*Time::GetDeltaTime();
		if (player->GetPosition().y < offsetPos.y)
		{
			SEMgr::UpdateFlag(6);
			state = 1;
			double randAngle = M_PI*GetRand(100) / 100.0;
			for (int i = 0; i < 8; i++)
			{
				enemyList.push_back(make_shared<Enemy04>(enemyList, offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight()), randAngle + 2 * M_PI / 8 * i));
			}
		}
		direction = player->GetPosition().x < offsetPos.x ? -1 : 1;
		break;
	case 1:
		offsetPos += Vector2<double>(300.0, 0.0)*direction*Time::GetDeltaTime();
		break;
	}

	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}

void Enemy03::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, 0.0, image[(int)type], TRUE, direction == 1);
}
