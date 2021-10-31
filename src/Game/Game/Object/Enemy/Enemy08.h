#pragma once

#include"Enemy.h"

class Enemy08 :public Enemy
{
private:
	static const double speed;
private:
	double angle;
private:
	void Move()override;
public:
	Enemy08(list<EnemyPtr>& enemyList, Vector2<double> position, double angle);
	~Enemy08();
	void Draw()override;
};