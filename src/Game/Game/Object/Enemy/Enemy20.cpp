#include"../header/Enemy20.h"
#include"../header/Time.h"

Enemy20::Enemy20(list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy20)
{
	timer = 0.0;
}

Enemy20::~Enemy20()
{

}

void Enemy20::Move()
{
	timer += Time::GetDeltaTime();
	position += Vector2<double>(300.0, 0.0)*(sin(2 * M_PI*1.0*timer))*Time::GetDeltaTime();
	position += Vector2<double>(0.0, 200.0)*(1.0 + sin(2 * M_PI*2.0*timer))*Time::GetDeltaTime();
}