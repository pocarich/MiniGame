#pragma once

/* leaf */

#include"Enemy.h"

class Enemy00 :public Enemy
{
private:
	double timer;
private:
	void Move()override;
public:
	Enemy00(list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy00();
};