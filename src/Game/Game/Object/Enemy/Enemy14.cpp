#include"../header/Enemy14.h"
#include"../header/Time.h"
#include"../header/Environment.h"

const double Enemy14::speed = 200.0;

Enemy14::Enemy14(list<EnemyPtr>& enemyList, Vector2<double> position,double angle) :Enemy(enemyList,position,EnemyType::Enemy14),angle(angle)
{
	offsetPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
}

Enemy14::~Enemy14()
{

}

void Enemy14::Move()
{
	offsetPos += Vector2<double>(cos(angle), sin(angle))*speed*Time::GetDeltaTime();
	position = offsetPos + Vector2<double>(0.0, Environment::GetCameraHeight());
}

void Enemy14::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, angle - M_PI / 2, image[(int)type], TRUE);
}