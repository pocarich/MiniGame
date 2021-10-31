#include"../header/Enemy17.h"
#include"../header/Time.h"
#include"../header/Environment.h"

const double Enemy17::speed = 400.0;

Enemy17::Enemy17(list<EnemyPtr>& enemyList, Vector2<double> position, double angle) :Enemy(enemyList, position, EnemyType::Enemy17), angle(angle)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
}

Enemy17::~Enemy17()
{

}

void Enemy17::Move()
{
	offsetPos += Vector2<double>(cos(angle), sin(angle))*speed*Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}