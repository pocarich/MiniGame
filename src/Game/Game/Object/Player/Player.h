#pragma once

#include"Define.h"
#include"Class.h"

class Player
{
private:
	static GHandle image;
	static GHandle balloonImage[5];
	static const double range;
private:
	list<BalloonPtr>& balloonList;
	list<ItemPtr>& itemList;
	list<EnemyPtr>& enemyList;
	list<EffectPtr>& effectList;

	Vector2<double> position;
	vector<int> heldBalloonList;

	int detectingItem;
	double attackedTimer;
public:
	static void Load();
private:
	void Move();
	void UpdateHeight();
	void AddBalloon(int type);
	void DetectCollision();
	void DetectItem();
	void CollideEnemy();
public:
	Player(list<BalloonPtr>& balloonList, list<ItemPtr>& itemList, list<EnemyPtr>& enemyList, list<EffectPtr>& effectList);
	~Player();
	void Update();
	void Draw();
	void ResetDetectingItem() { detectingItem = -1; }

	int GetDetectingItem()const { return detectingItem; }
	Vector2<double> GetPosition()const { return position; }
	int GetBalloonNum()const { return heldBalloonList.size(); }
};