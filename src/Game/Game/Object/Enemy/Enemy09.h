#pragma once

#include"Enemy.h"

class Enemy09 :public Enemy
{
private:
	static const double speed;
private:
	double angle;
private:
	void Move()override;
public:
	Enemy09(list<EnemyPtr>& enemyList, Vector2<double> position,double angle);
	~Enemy09();
	void Draw()override;
};