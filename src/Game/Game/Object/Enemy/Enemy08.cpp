#include"../header/Enemy08.h"
#include"../header/Time.h"
#include"../header/Environment.h"

const double Enemy08::speed = 100.0;

Enemy08::Enemy08(list<EnemyPtr>& enemyList, Vector2<double> position,double angle) :Enemy(enemyList,position,EnemyType::Enemy08),angle(angle)
{
	
}

Enemy08::~Enemy08()
{

}

void Enemy08::Move()
{
	position += Vector2<double>(cos(angle), sin(angle))*speed*Time::GetDeltaTime();
}

void Enemy08::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, angle - M_PI / 2, image[(int)type], TRUE);
}