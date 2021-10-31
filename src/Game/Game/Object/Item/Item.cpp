#include"../header/Item.h"
#include"../header/Environment.h"

GHandle Item::image;
const double Item::range = 50.0;

void Item::Load()
{
	image = LoadGraph("data/graph/character/item0.png");
}

Item::Item(Vector2<double> position):position(position)
{
	deathFlag = false;
}

Item::~Item()
{

}

void Item::Update()
{
	if ((float)(position.y - Environment::GetCameraHeight()) > Define::WINDOW_HEIGHT + 300)
	{
		deathFlag = true;
	}
}

void Item::Collided()
{
	deathFlag = true;
}

void Item::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, 0.0, image, TRUE);
}