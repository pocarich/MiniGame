#pragma once

#include"Define.h"
#include"Class.h"

class Effect
{
public:
	enum struct EffectType
	{
		BALLOON,
		BURSt
	};
protected:
	Vector2<double> position;
	int animationFrameCounter;
	EffectType type;
	bool deathFlag;
public:
	Effect(Vector2<double> position, EffectType type);
	virtual ~Effect();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool GetDeathFlag()const { return deathFlag; }
};