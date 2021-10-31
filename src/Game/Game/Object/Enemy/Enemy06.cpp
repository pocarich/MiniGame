#include"../header/Enemy06.h"
#include"../header/Time.h"
#include"../header/Environment.h"

Enemy06::Enemy06(list<EnemyPtr>& enemyList, Vector2<double> position,int direction) :Enemy(enemyList,position,EnemyType::Enemy06),direction(direction)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
}

Enemy06::~Enemy06()
{

}

void Enemy06::Move()
{
	offsetPos += Vector2<double>(300.0, 0.0)*direction*Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}

void Enemy06::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, 0.0, image[(int)type], TRUE, direction == 1);
}