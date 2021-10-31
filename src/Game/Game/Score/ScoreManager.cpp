#include"../header/ScoreManager.h"

vector<int> ScoreManager::savedScoreList;
int ScoreManager::rank;

void ScoreManager::Load()
{
	ifstream ifs("data/text/save.txt");

	assert(!ifs.fail() && "ScoreManager::Load()");

	string str;

	for (int i = 0; i < Define::MAX_SAVED_SCORE_NUM; i++)
	{
		getline(ifs, str);
		stringstream ss;
		ss << str;
		int n;
		ss >> n;
		savedScoreList.push_back(n);
	}
}

void ScoreManager::UpdateScore(int score)
{
	rank = -1;
	for (int i = 0; i != savedScoreList.size(); i++)
	{
		if (savedScoreList[i] <= score)
		{
			rank = i;
			break;
		}
	}

	savedScoreList.push_back(score);
	sort(savedScoreList.begin(), savedScoreList.end(), greater<int>());
	savedScoreList.pop_back();
}

void ScoreManager::Save()
{
	ofstream ofs("data/text/save.txt");

	assert(!ofs.fail() && "ScoreManager::Save()");

	for (int i = 0; i < Define::MAX_SAVED_SCORE_NUM; i++)
	{
		ofs << savedScoreList[i] << endl;
	}
}