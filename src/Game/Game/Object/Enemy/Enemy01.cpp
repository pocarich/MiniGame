#include"../header/Enemy01.h"
#include"../header/Time.h"
#include"../header/Environment.h"

Enemy01::Enemy01(list<EnemyPtr>& enemyList, Vector2<double> position,int direction) :Enemy(enemyList,position,EnemyType::Enemy01),direction(direction)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
}

Enemy01::~Enemy01()
{

}

void Enemy01::Move()
{
	offsetPos += Vector2<double>(200.0,0.0)*direction*Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}

void Enemy01::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, 0.0, image[(int)type], TRUE, direction == 1);
}
