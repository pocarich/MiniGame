#pragma once

#include"Enemy.h"
#include"Player.h"

class Enemy12 :public Enemy
{
private:
	static const double speed;
	static const double maxDeltaAngle;
private:
	const Player* player;
	Vector2<double> offsetPos;
	double timer;
	double angle;
	double animTimer;
	bool animFlag;
private:
	void Move()override;
public:
	Enemy12(const Player* player,list<EnemyPtr>& enemyList, Vector2<double> position,int direction);
	~Enemy12();
	void Draw()override;
};