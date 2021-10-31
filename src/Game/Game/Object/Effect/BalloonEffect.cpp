#include"../header/BalloonEffect.h"
#include"../header/Time.h"

array<GHandle, 5> BalloonEffect::image;

void BalloonEffect::Load()
{
	for (int i = 0; i < 5; i++)
	{
		stringstream ss;
		ss << "data/graph/character/balloon" << i << ".png";
		image[i] = LoadGraph(ss.str().c_str());
	}
}

BalloonEffect::BalloonEffect(Vector2<double> position, int colorType) :Effect(position, EffectType::BALLOON), colorType(colorType)
{
	timer = 0.0;
	xspeed = -50 + 100 * GetRand(100) / 100.0;
}

BalloonEffect::~BalloonEffect()
{

}

void BalloonEffect::Update()
{
	position += Vector2<double>(xspeed, -300.0*timer)*Time::GetDeltaTime();
	if (position.y < -200.0)
	{
		deathFlag = true;
	}
	timer += Time::GetDeltaTime();
}

void BalloonEffect::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y), 1.0, 0.0, image[colorType], TRUE);
}