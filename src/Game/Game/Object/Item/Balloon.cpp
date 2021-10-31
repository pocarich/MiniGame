#include"../header/Balloon.h"
#include"../header/Environment.h"

array<GHandle, 5> Balloon::image;
const double Balloon::range = 50.0;

void Balloon::Load()
{
	for (int i = 0; i < 5; i++)
	{
		stringstream ss;
		ss << "data/graph/character/balloon" << i << ".png";
		image[i] = LoadGraph(ss.str().c_str());
	}
}

Balloon::Balloon(Vector2<double> position) :position(position)
{
	color = GetRand(100) % 5;
	deathFlag = false;
}

Balloon::~Balloon()
{

}

void Balloon::Update()
{
	if ((float)(position.y - Environment::GetCameraHeight()) > Define::WINDOW_HEIGHT + 300)
	{
		deathFlag = true;
	}
}

void Balloon::Collided()
{
	deathFlag = true;
}

void Balloon::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, 0.0, image[color], TRUE);
}