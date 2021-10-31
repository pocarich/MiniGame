#include"../header/Enemy16.h"
#include"../header/Time.h"
#include"../header/Environment.h"

const double Enemy16::speed = 700.0;

Enemy16::Enemy16(list<EnemyPtr>& enemyList, Vector2<double> position,double angle) :Enemy(enemyList,position,EnemyType::Enemy16),angle(angle)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
}

Enemy16::~Enemy16()
{

}

void Enemy16::Move()
{
	offsetPos += Vector2<double>(cos(angle), sin(angle))*speed*Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}