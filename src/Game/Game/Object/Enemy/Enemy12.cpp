#include"../header/Enemy12.h"
#include"../header/Time.h"
#include"../header/Environment.h"
#include"../header/Enemy11.h"
#include"../header/SEMgr.h"

const double Enemy12::speed = 150.0;
const double Enemy12::maxDeltaAngle = M_PI;

Enemy12::Enemy12(const Player* player,list<EnemyPtr>& enemyList, Vector2<double> position,int direction) :Enemy(enemyList,position,EnemyType::Enemy12),player(player)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
	timer = 0.0;
	animTimer = 0.0;
	animFlag = false;
	if (direction == 1)
	{
		angle = 0.0;
	}
	else
	{
		angle = M_PI;
	}
}

Enemy12::~Enemy12()
{

}


void Enemy12::Move()
{
	if (timer > 8.0)
	{
		SEMgr::UpdateFlag(7);
		double randAngle = M_PI*GetRand(100) / 100.0;
		for (int i = 0; i < 12; i++)
		{
			enemyList.push_back(make_shared<Enemy11>(enemyList, offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight()), randAngle + 2 * M_PI / 12 * i));
		}
		deathFlag = true;
	}

	if (0.0 <= offsetPos.x&&offsetPos.x <= Define::WINDOW_WIDTH&&0.0 <= offsetPos.y&&offsetPos.y <= Define::WINDOW_HEIGHT)
	{
		double diffAngle = atan2(player->GetPosition().y - offsetPos.y, player->GetPosition().x - offsetPos.x) - angle;
		if (diffAngle > M_PI)diffAngle -= 2 * M_PI;
		if (diffAngle < -M_PI)diffAngle += 2 * M_PI;
		if (abs(diffAngle) > 0.0000001)
		{
			angle += min(diffAngle, diffAngle / abs(diffAngle)*maxDeltaAngle*Time::GetDeltaTime());
		}
	}
	timer += Time::GetDeltaTime();
	offsetPos +=Vector2<double>(cos(angle), sin(angle))*speed*Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}

void Enemy12::Draw()
{
	if (timer < 10.0)
	{
		DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, angle, image[(int)type], TRUE);
	}
	else
	{
		animTimer += Time::GetDeltaTime();
		if (animTimer > 0.1)
		{
			animFlag = !animFlag;
		}
		if (animFlag)
		{
			DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, angle, image[(int)type], TRUE);
		}
	}
}