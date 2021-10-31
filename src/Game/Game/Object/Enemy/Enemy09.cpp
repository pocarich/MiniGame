#include"../header/Enemy09.h"
#include"../header/Time.h"
#include"../header/Environment.h"
#include"../header/SEMgr.h"

const double Enemy09::speed = 150.0;

Enemy09::Enemy09(list<EnemyPtr>& enemyList, Vector2<double> position,double angle) :Enemy(enemyList,position,EnemyType::Enemy09),angle(angle)
{
	SEMgr::UpdateFlag(5);
}

Enemy09::~Enemy09()
{

}

void Enemy09::Move()
{
	position += Vector2<double>(cos(angle), sin(angle))*speed*Time::GetDeltaTime();
}

void Enemy09::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, angle - M_PI / 2, image[(int)type], TRUE);
}