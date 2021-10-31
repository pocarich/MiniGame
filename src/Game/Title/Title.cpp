#include"../header/Title.h"
#include"../header/KeyBoard.h"
#include"../header/BGMMgr.h"
#include"../header/SEMgr.h"
#include"../header/Function.h"
#include"../header/Mouse.h"

GHandle Title::backImage;

void Title::Load()
{
	backImage = LoadGraph("data/graph/common/title_back.jpg");
}

Title::Title(ScoreManager* scoreManager):scoreManager(scoreManager)
{
	stateEndFlag = false;
	pushStartFlag = false;
	timer = 0;
	endTimer = 0;
	darkAlpha = 0;
}

Title::~Title()
{
	
}

void Title::Update()
{
	if (!pushStartFlag)
	{
		timer++;
		if (Mouse::ClickOnce(MOUSE_INPUT_LEFT))
		{
			SEMgr::UpdateFlag(0);
			pushStartFlag = true;
		}
	}
	else
	{
		darkAlpha += 3;
		darkAlpha = min(255, darkAlpha);
		endTimer++;
		if (endTimer == 120)
		{
			stateEndFlag = true;
		}
	}
}

void Title::Draw()
{
	DrawGraph(0, 0, backImage, FALSE);

	if (!pushStartFlag)
	{
		if ((timer / 30) % 2 == 0)
		{
			DrawFormatStringToHandle(Define::WINDOW_WIDTH / 2 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[21], "マウスをひだりクリックしてスタート！！") / 2, Define::WINDOW_HEIGHT / 2 + 180, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[21], "マウスをひだりクリックしてスタート！！");
		}
	}
	else
	{
		if ((endTimer / 5) % 2 == 0)
		{
			DrawFormatStringToHandle(Define::WINDOW_WIDTH / 2 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[21], "マウスをひだりクリックしてスタート！！") / 2, Define::WINDOW_HEIGHT / 2 + 180, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[21], "マウスをひだりクリックしてスタート！！");
		}
	}

	Function::Alpha(darkAlpha);

	DrawFillBox(0, 0, Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);

	Function::Alpha(255);
}
