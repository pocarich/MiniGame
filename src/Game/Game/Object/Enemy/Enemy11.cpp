#include"../header/Enemy11.h"
#include"../header/Time.h"
#include"../header/Environment.h"

const double Enemy11::speed = 250.0;

Enemy11::Enemy11(list<EnemyPtr>& enemyList, Vector2<double> position,double angle) :Enemy(enemyList,position,EnemyType::Enemy11),angle(angle)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
}

Enemy11::~Enemy11()
{

}

void Enemy11::Move()
{
	offsetPos += Vector2<double>(cos(angle), sin(angle))*speed*Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}