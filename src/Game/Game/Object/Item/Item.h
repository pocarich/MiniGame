#pragma once

#include"Define.h"
#include"Class.h"

class Item
{
private:
	static GHandle image;
	static const double range;
private:
	Vector2<double> position;
	bool deathFlag;
public:
	static void Load();
public:
	Item(Vector2<double> position);
	~Item();
	void Update();
	void Draw();
	void Collided();
	double GetRange()const { return range; }
	Vector2<double> GetPosition()const { return position; }
	bool GetDeathFlag()const { return deathFlag; }
};