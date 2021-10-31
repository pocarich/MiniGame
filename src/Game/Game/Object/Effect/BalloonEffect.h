#pragma once

#include"Define.h"
#include"Effect.h"

class BalloonEffect:public Effect
{
private:
	static array<GHandle, 5> image;
private:
	int colorType;
	double timer;
	double xspeed;
public:
	static void Load();
public:
	BalloonEffect(Vector2<double> position, int colorType);
	~BalloonEffect();
	void Update()override;
	void Draw()override;
};