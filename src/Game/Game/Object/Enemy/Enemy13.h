#pragma once

#include"Enemy.h"

class Enemy13 :public Enemy
{
private:
	Vector2<double> offsetPos;
	double timer;
	array<double, 2> attackTimer;
	double attackAngle;
	int attackState;
private:
	void Move()override;
public:
	Enemy13(list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy13();
};