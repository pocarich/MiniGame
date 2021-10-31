#include"../header/SystemMgr.h"
#include"../header/KeyBoard.h"
#include"../header/ColorMgr.h"
#include"../header/FontMgr.h"
#include"../header/SEMgr.h"
#include"../header/BGMMgr.h"
#include"../header/Game.h"
#include"../header/Time.h"
#include"../header/Player.h"
#include"../header/ObjectSpawnInfoList.h"
#include"../header/Balloon.h"
#include"../header/Item.h"
#include"../header/Enemy.h"
#include"../header/Environment.h"
#include"../header/ScoreManager.h"
#include"../header/Mouse.h"
#include"../header/BalloonEffect.h"
#include"../header/Title.h"

SystemMgr::SystemMgr()
{
	SetMainWindowText("BALLOON TRIP");
	ChangeWindowMode(TRUE);
	SetGraphMode(Define::WINDOW_WIDTH, Define::WINDOW_HEIGHT, 16);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	AddFont();

	ColorMgr::Load();
	FontMgr::Load();
	SEMgr::Load();
	BGMMgr::Load();
	Game::Load();
	KeyBoard::Init();
	Player::Load();
	ObjectSpawnInfoList::Load();
	Balloon::Load();
	BalloonEffect::Load();
	Item::Load();
	Title::Load();
	Enemy::Load();
	ScoreManager::Load();

	gameMgr = new GameMgr();
	fpsMgr = new FPSMgr();
}

SystemMgr::~SystemMgr()
{
	DxLib_End();
	DeleteFont();

	delete gameMgr;
	delete fpsMgr;
}

void SystemMgr::AddFont()
{
	string fontPath = "data/font/ExtraFont0.ttf";
	if (!(AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL) > 0))
	{
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
}

void SystemMgr::DeleteFont()
{
	string fontPath = "data/font/ExtraFont0.ttf";

	if (!(RemoveFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL)))
	{
		MessageBox(NULL, "remove failure", "", MB_OK);
	}
}

void SystemMgr::Loop()
{
	BGMMgr::UpdateStartFlag(0);
	while (Process())
	{
		KeyBoard::Update();									   //キーボード入力の更新
		Mouse::Update();
		BGMMgr::Play();
		SEMgr::Play();
		Time::UpdateTime();
		gameMgr->Main();                                       //ゲームのメイン処理
		fpsMgr->Main();
	}
}

bool SystemMgr::Process()
{
	if (ScreenFlip())return false;								//裏画面を表画面にコピー
	if (ProcessMessage())return false;							//ウィンドウのメッセージ処理
	if (ClearDrawScreen())return false;							//裏画面のクリア
	if (KeyBoard::PushOnce(KEY_INPUT_ESCAPE))return false;
	return true;
}