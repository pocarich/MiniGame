#pragma once

#include"Enemy.h"
#include"Player.h"

class Enemy02 :public Enemy
{
private:
	const Player* player;

	double timer;
	int direction;
	int nowDirection;
	int counter;
	Vector2<double> prePos;
	Vector2<double> nextPos;
	Vector2<double> offsetPos;
private:
	void Move()override;
public:
	Enemy02(const Player* player,list<EnemyPtr>& enemyList,int direction);
	~Enemy02();
	void Draw()override;
};