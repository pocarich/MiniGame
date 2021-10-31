#include"../header/ObjectSpawnInfoList.h"
#include"../header/Function.h"

vector<ObjectSpawnInfoList::ObjectSpawnInfo> ObjectSpawnInfoList::objectSpawnInfoList;

void ObjectSpawnInfoList::Load()
{
	ifstream ifs("data/csv/objectSpawnInfo.csv");

	assert(!ifs.fail() && "ObjectSpawnInfoList::Load()");

	string str;

	while (getline(ifs, str))
	{
		vector<string> element = Function::split(str, ',');
		assert(element.size() == 7 && "ObjectSpawnInfoList::Load()");
		ObjectSpawnInfo osi;
		for (int i = 0; i != element.size(); i++)
		{
			stringstream ss;
			ss << element[i];
			int n;
			switch (i)
			{
			case 0:
				ss >> osi.spawnHeight;
				break;
			case 1:
				ss >> n;
				osi.objectID = (ObjectID)n;
				break;
			case 2:
				ss >> osi.type;
				break;
			case 3:
				ss >> osi.option;
				break;
			case 4:
				ss >> osi.position.x;
				break;
			case 5:
				ss >> osi.position.y;
				break;
			case 6:
				ss >> osi.value;
				break;
			}
		}
		objectSpawnInfoList.push_back(osi);
	}

	sort(objectSpawnInfoList.begin(), objectSpawnInfoList.end(), [&](ObjectSpawnInfo& src, ObjectSpawnInfo dist) {return src.spawnHeight < dist.spawnHeight; });
}