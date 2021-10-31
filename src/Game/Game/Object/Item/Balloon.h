#pragma once

#include"Define.h"
#include"Class.h"

class Balloon
{
private:
	static array<GHandle, 5> image;
	static const double range;
private:
	Vector2<double> position;
	int color;
	bool deathFlag;
public:
	static void Load();
public:
	Balloon(Vector2<double> position);
	~Balloon();
	void Update();
	void Draw();
	void Collided();
	Vector2<double> GetPosition()const { return position; }
	int GetBalloonColor()const { return color; }
	bool GetDeathFlag()const { return deathFlag; }
	double GetRange()const { return range; }
};