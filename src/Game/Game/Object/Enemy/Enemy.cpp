#include"../header/Enemy.h"
#include"../header/Environment.h"
#include"../header/Function.h"
#include"../header/Time.h"

array<GHandle, 21> Enemy::image;
array<double, 21> Enemy::range;

void Enemy::Load()
{
	for (int i = 0; i < 21; i++)
	{
		stringstream ss;
		ss << "data/graph/character/enemy" << Function::NumToStringFillZero(i,2) << ".png";
		image[i] = LoadGraph(ss.str().c_str());
	}

	ifstream ifs("data/csv/rangeInfo.csv");

	assert(!ifs.fail() && "Enemy::Load()");

	string str;

	int index = 0;
	while (getline(ifs, str))
	{
		vector<string> element = Function::split(str, ',');
		assert(element.size() == 1 && "Enemy::Load()");

		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			ss << element[i];
			int n;
			switch (i)
			{
			case 0:
				ss >> range[index];
				break;
			}
		}
		index++;
	}
}

Enemy::Enemy(list<EnemyPtr>& enemyList,Vector2<double> position,EnemyType type) :enemyList(enemyList),position(position),type(type)
{
	deathFlag = false;
	isCollided = false;
	isShown = false;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	Move();
	UpdateExist();
}

void Enemy::Move()
{

}

void Enemy::UpdateExist()
{
	Vector2<double> tempPos = position - Vector2<double>(0.0, Environment::GetCameraHeight());
	if (-200.0 <= tempPos.x&&tempPos.x <= Define::WINDOW_WIDTH+200.0&&-200.0 <= tempPos.y&&tempPos.y <= Define::WINDOW_HEIGHT+200.0)
	{
		isShown = true;
	}
	else
	{
		if (isShown)
		{
			deathFlag = true;
		}
	}

	existingTimer += Time::GetDeltaTime();
	if (!isShown&&existingTimer > 10.0)
	{
		deathFlag = true;
	}
}

void Enemy::Collided()
{
	isCollided = true;
}

void Enemy::Draw()
{
	DrawRotaGraphF((float)(position.x), (float)(position.y - Environment::GetCameraHeight()), 1.0, 0.0, image[(int)type], TRUE);
}
