#pragma once

#include"Enemy.h"

class Enemy16 :public Enemy
{
private:
	Vector2<double> offsetPos;
	static const double speed;
private:
	double angle;
private:
	void Move()override;
public:
	Enemy16(list<EnemyPtr>& enemyList, Vector2<double> position,double angle);
	~Enemy16();
};