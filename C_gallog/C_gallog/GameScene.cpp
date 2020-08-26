#include "GameScene.h"
#pragma warning(disable:4996)
void GameScene::Init(SceneManager& pSceneManager)
{
	mEnemy.clear();
	mEnemyMakeTime = 0;
	
	System::getInstance()->SetScore(0);
	System::getInstance()->SetCollision(FALSE);
	m_Character.Init();
}

void GameScene::Update(float dt)
{
	if (GetTickCount() - mEnemyMakeTime > 1000)
	{
		mEnemyMakeTime = GetTickCount();

		Enemy temp;
		temp.SetPosX(42);
		temp.SetPosY(rand() % 16 + 4);
		temp.Update(dt);
		temp.SetBullet(m_Character.GetBullet());
		mEnemy.push_back(temp);
	}
	
	for (auto itor = mEnemy.begin(); itor != mEnemy.end();)
	{
		if (itor->m_Remove)
			itor = mEnemy.erase(itor);

		else
		{
			itor->Update(dt);
			itor++;
		}
	}
	
		
	if (GetAsyncKeyState(VK_ESCAPE))
		System::getInstance()->GetSM()->reserveChangeScene("MenuScene");		
	
	if(!System::getInstance()->GetCollision())
		m_Character.Update(dt);

}

void GameScene::Render(float dt)
{
	SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), YELLOW);
	for (auto itor = mEnemy.begin(); itor != mEnemy.end(); ++itor)
		itor->Render(dt);
	SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE);

	m_Character.Render(dt);
	
	DrawMap();
	GameUI();
}

void GameScene::Destroy()
{
	m_Character.Destroy();

	for (auto itor = mEnemy.begin(); itor != mEnemy.end(); ++itor)
		itor->Destroy();
}

void GameScene::DrawMap()
{
	// 테두리
	for (int i = 0; i < 40; i++)
	{
		System::getInstance()->GetDB()->WriteBuffer(i * 2 + 3, 2, "■");
		System::getInstance()->GetDB()->WriteBuffer(i * 2 + 3, 22, "■");
	}

	for (int i = 0; i < 21; i++)
	{
		System::getInstance()->GetDB()->WriteBuffer(3, i + 2, "■");
		System::getInstance()->GetDB()->WriteBuffer(83, i + 2, "■");
	}

	
}

void GameScene::GameUI()
{
	// 게임 종료
	if (System::getInstance()->GetCollision())
	{
		SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), RED << 4);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				System::getInstance()->GetDB()->WriteBuffer(j * 2 + 34, i + 7, "　");
			}
		}

		SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE | RED << 4);
		System::getInstance()->GetDB()->WriteBuffer(40, 12, "게임종료");
		System::getInstance()->GetDB()->WriteBuffer(37, 13, "ESC를 누르세요");

		SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), YELLOW);
		for (int i = 0; i < 10; i++)
		{
			System::getInstance()->GetDB()->WriteBuffer(i * 2 + 34, 7, "■");
			System::getInstance()->GetDB()->WriteBuffer(i * 2 + 34, 17, "■");
		}
		for (int i = 0; i < 10; i++)
		{
			System::getInstance()->GetDB()->WriteBuffer(34, i + 8, "■");
			System::getInstance()->GetDB()->WriteBuffer(52, i + 8, "■");
		}

		SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE | BLACK << 4);
	}

	char str[128];
	SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), YELLOW);
	sprintf(str, "점수 : %d점", System::getInstance()->GetScore());
	System::getInstance()->GetDB()->WriteBuffer(3, 23, str);
	SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE);

}

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}
