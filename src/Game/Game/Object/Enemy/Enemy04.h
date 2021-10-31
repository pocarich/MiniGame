#pragma once

#include"Enemy.h"

class Enemy04 :public Enemy
{
private:
	static const double speed;
private:
	double angle;
	Vector2<double> offsetPos;
private:
	void Move()override;
public:
	Enemy04(list<EnemyPtr>& enemyList, Vector2<double> position,double angle);
	~Enemy04();
	void Draw()override;
};