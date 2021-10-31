#pragma once

#include"Enemy.h"

class Enemy14 :public Enemy
{
private:
	Vector2<double> offsetPos;
	static const double speed;
private:
	double angle;
private:
	void Move()override;
public:
	Enemy14(list<EnemyPtr>& enemyList, Vector2<double> position,double angle);
	~Enemy14();
	void Draw()override;
};