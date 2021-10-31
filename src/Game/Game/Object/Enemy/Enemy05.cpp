#include"../header/Enemy05.h"
#include"../header/Time.h"

Enemy05::Enemy05(list<EnemyPtr>& enemyList, Vector2<double> position) :Enemy(enemyList,position,EnemyType::Enemy05)
{
	
}

Enemy05::~Enemy05()
{

}

void Enemy05::Move()
{
	position += Vector2<double>(0.0, 50.0)*Time::GetDeltaTime();
}
