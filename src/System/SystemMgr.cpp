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
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
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
		KeyBoard::Update();									   //�L�[�{�[�h���͂̍X�V
		Mouse::Update();
		BGMMgr::Play();
		SEMgr::Play();
		Time::UpdateTime();
		gameMgr->Main();                                       //�Q�[���̃��C������
		fpsMgr->Main();
	}
}

bool SystemMgr::Process()
{
	if (ScreenFlip())return false;								//����ʂ�\��ʂɃR�s�[
	if (ProcessMessage())return false;							//�E�B���h�E�̃��b�Z�[�W����
	if (ClearDrawScreen())return false;							//����ʂ̃N���A
	if (KeyBoard::PushOnce(KEY_INPUT_ESCAPE))return false;
	return true;
}