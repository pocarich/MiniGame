#pragma once

#include"Enemy.h"

class Enemy19 :public Enemy
{
private:
	double timer;
private:
	void Move()override;
public:
	Enemy19(list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy19();
};