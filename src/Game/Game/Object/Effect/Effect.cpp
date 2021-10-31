#include"../header/Effect.h"

Effect::Effect(Vector2<double> position, EffectType type) :position(position), type(type)
{
	animationFrameCounter = 0;
	deathFlag = false;
}

Effect::~Effect()
{

}