#pragma once

#include"Enemy.h"

class Enemy06 :public Enemy
{
private:
	Vector2<double> offsetPos;
	int direction;
private:
	void Move()override;
public:
	Enemy06(list<EnemyPtr>& enemyList, Vector2<double> position,int direction);
	~Enemy06();
	void Draw()override;
};