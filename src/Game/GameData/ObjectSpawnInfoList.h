#pragma once

#include"Define.h"
#include"Class.h"

class ObjectSpawnInfoList
{
public:
	class ObjectSpawnInfo
	{
	public:
		double spawnHeight;
		ObjectID objectID;
		int type;
		int option;
		Vector2<double> position;
		int value;
	};
private:
	static vector<ObjectSpawnInfo> objectSpawnInfoList;
public:
	static void Load();
	static const vector<ObjectSpawnInfo>& GetObjectSpawnInfoList() { return objectSpawnInfoList; }
};