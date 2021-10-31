#pragma once

/* bee */

#include"Enemy.h"

class Enemy01 :public Enemy
{
private:
	Vector2<double> offsetPos;
	int direction;
private:
	void Move()override;
public:
	Enemy01(list<EnemyPtr>& enemyList, Vector2<double> position,int direction);
	~Enemy01();
	void Draw()override;
};