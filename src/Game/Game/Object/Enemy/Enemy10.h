#pragma once

#include"Enemy.h"
#include"Player.h"

class Enemy10 :public Enemy
{
private:
	const Player* player;
	Vector2<double> offsetPos;
	double timer;
	array<double,2> attackAngle;
	array<double,2> attackTimer;
private:
	void Move()override;
public:
	Enemy10(const Player* player,list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy10();
};