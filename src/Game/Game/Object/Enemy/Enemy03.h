#pragma once

#include"Enemy.h"
#include"Player.h"

class Enemy03 :public Enemy
{
private:
	const Player* player;
	int state;
	Vector2<double> offsetPos;
	int direction;
private:
	void Move()override;
public:
	Enemy03(const Player* player,list<EnemyPtr>& enemyList, Vector2<double> position);
	~Enemy03();
	void Draw()override;
};