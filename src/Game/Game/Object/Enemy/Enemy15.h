#pragma once

#include"Enemy.h"
#include"Player.h"

class Enemy15 :public Enemy
{
private:
	const Player* player;
	Vector2<double> offsetPos;
	double startTimer;
	double timer;
	double attackTimer;
	int state;
	int sw;
private:
	void Move()override;
public:
	Enemy15(const Player* player,list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy15();
};