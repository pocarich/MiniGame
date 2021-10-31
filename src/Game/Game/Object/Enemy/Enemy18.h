#pragma once

#include"Enemy.h"

class Enemy18 :public Enemy
{
private:
	Vector2<double> offsetPos;
	double ySpeed;
	double timer;
	bool seFlag;
private:
	void Move()override;
public:
	Enemy18(list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy18();
};