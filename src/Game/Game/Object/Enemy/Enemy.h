#pragma once

#include"Define.h"
#include"Class.h"

class Enemy
{
protected:
	static array<GHandle, 21> image;
	static array<double, 21> range;
public:
	enum struct EnemyType
	{
		Enemy00,
		Enemy01,
		Enemy02,
		Enemy03,
		Enemy04,
		Enemy05,
		Enemy06,
		Enemy07,
		Enemy08,
		Enemy09,
		Enemy10,
		Enemy11,
		Enemy12,
		Enemy13,
		Enemy14,
		Enemy15,
		Enemy16,
		Enemy17,
		Enemy18,
		Enemy19,
		Enemy20,
	};
protected:
	list<EnemyPtr>& enemyList;

	Vector2<double> position;
	EnemyType type;
	bool deathFlag;
	bool isCollided;
	bool isShown;
	double existingTimer;
public:
	static void Load();
protected:
	virtual void Move();
	virtual void UpdateExist();
public:
	Enemy(list<EnemyPtr>& enemyList,Vector2<double> position,EnemyType type);
	virtual ~Enemy();
	virtual void Update();
	virtual void Draw();
	void Collided();
	Vector2<double> GetPosition()const { return position; }
	bool GetDeathFlag()const { return deathFlag; }
	EnemyType GetType()const { return type; }
	bool IsCollided()const { return isCollided; }
	double GetRange()const { return range[(int)type]; }
};