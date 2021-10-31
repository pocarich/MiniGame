#include"../header/Enemy04.h"
#include"../header/Time.h"
#include"../header/Environment.h"

const double Enemy04::speed = 100.0;

Enemy04::Enemy04(list<EnemyPtr>& enemyList, Vector2<double> position,double angle) :Enemy(enemyList,position,EnemyType::Enemy04),angle(angle)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
}

Enemy04::~Enemy04()
{

}

void Enemy04::Move()
{
	offsetPos += Vector2<double>(cos(angle), sin(angle))*speed*Time::GetDeltaTime();

	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}

void Enemy04::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, angle+M_PI/2, image[(int)type], TRUE);
}
