#pragma once

#include"Enemy.h"

class Enemy20 :public Enemy
{
private:
	double timer;
private:
	void Move()override;
public:
	Enemy20(list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy20();
};