#pragma once

#include<Dxlib.h>
#include<fstream>
#include<sstream>
#include<memory>
#include<string>
#include<array>
#include<vector>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<typeinfo>
#include<assert.h>
#include<algorithm>
#include<numeric>
#include<functional>
#include<assert.h>
#include<cstdio>
#include<iostream>
#include<Windows.h>
#include<queue>
#include<set>
#include<iomanip>
#include<random>

#define _USE_MATH_DEFINES
#include<math.h>

#define STR(var) #var

using namespace std;

class Define
{
public:
	static const int FPS = 60;
	static const int BASE_WINDOW_WIDTH = 1000;
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 600;
	static const int MAX_SAVED_SCORE_NUM = 7;
	static const double ATTACKED_TIME;
	static const double DEFAULT_SPEED;
	static const double ADD_SPEED;

	static const double LIMIT_TIME;

	static const int MAX_HELD_BALLOON_NUM = 10;

	static const double PLAYER_SPEED;
	static const double PLAYER_HI_SPEED_RAIO;
	static const double ADD_TIMER;
	static const int BACK_SKY_NUM = 5;
	static const int BACK_SPACE_NUM = 11;
	static const int BACK_HEAVEN_NUM = 20;
private:
	Define() {};
	Define(const Define&) {};
	Define& operator =(const Define&) {};
};

enum struct ObjectID
{
	BALLOON,
	ITEM,
	ENEMY
};

typedef int GHandle;
typedef int MHandle;
typedef int FHandle;
typedef int Color;
typedef int Font;

class MapObject;
typedef shared_ptr<MapObject> MapObjectPtr;
class PlayerMap;
typedef shared_ptr<PlayerMap> PlayerMapPtr;
class MonsterMap;
typedef shared_ptr<MonsterMap> MonsterMapPtr;
class BattleObject;
typedef shared_ptr<BattleObject> BattleObjectPtr;
class PlayerBattle;
typedef shared_ptr<PlayerBattle> PlayerBattlePtr;
class MonsterBattle;
typedef shared_ptr<MonsterBattle> MonsterBattlePtr;
class Window;
typedef shared_ptr<Window> WindowPtr;
class Balloon;
typedef shared_ptr<Balloon> BalloonPtr;
class Item;
typedef shared_ptr<Item> ItemPtr;
class Enemy;
typedef shared_ptr<Enemy> EnemyPtr;
class Effect;
typedef shared_ptr<Effect> EffectPtr;