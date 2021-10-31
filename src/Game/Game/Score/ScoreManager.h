#pragma once

#include"Define.h"

class ScoreManager
{
private:
	static vector<int> savedScoreList;
	static int rank;
public:
	static void Load();
	static void Save();
	static void UpdateScore(int score);
	static const vector<int>& GetSavedScoreList() { return savedScoreList; }
	static int GetRank() { return rank; }
};