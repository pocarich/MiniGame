#include"../header/Enemy00.h"
#include"../header/Time.h"

Enemy00::Enemy00(list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy00)
{
	timer = 0.0;
}

Enemy00::~Enemy00()
{

}

void Enemy00::Move()
{
	timer += Time::GetDeltaTime();
	position += Vector2<double>(300.0, 0.0)*(sin(2 * M_PI*1.0*timer))*Time::GetDeltaTime();
	position += Vector2<double>(0.0, 100.0)*(1.0 + sin(2 * M_PI*2.0*timer))*Time::GetDeltaTime();
}