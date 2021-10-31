#pragma once

#include"Enemy.h"

class Enemy07 :public Enemy
{
private:
	double timer;
	double attackTimer;
	Vector2<double> offsetPos;
private:
	void Move()override;
public:
	Enemy07(list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy07();
};