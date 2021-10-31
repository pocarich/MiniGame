#pragma once

#include"Enemy.h"

class Enemy05 :public Enemy
{
private:
	void Move()override;
public:
	Enemy05(list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy05();
};