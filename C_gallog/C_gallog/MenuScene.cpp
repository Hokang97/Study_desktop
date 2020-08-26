#include "MenuScene.h"

void MenuScene::Init(SceneManager& pSceneManager)
{
}

void MenuScene::Update(float dt)
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		selectMenu = MENU_EXIT;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		selectMenu = MENU_START;
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (selectMenu)
		{
		case MENU_START:
			System::getInstance()->GetSM()->reserveChangeScene("GameScene");
			break;

		case MENU_EXIT:
			System::getInstance()->SetExit(TRUE);
			break;
		}
	}
}

void MenuScene::Render(float dt)
{
	DrawMenu();
}

void MenuScene::Destroy()
{
}

void MenuScene::DrawMenu()
{	
	// 테두리

	SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), BLACK << 4);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			System::getInstance()->GetDB()->WriteBuffer(j * 2 + 34, i + 7, "　");
		}
	}

	SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE);
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
	
	


	switch (selectMenu)
	{
	case MENU_START:
		SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), YELLOW);
		System::getInstance()->GetDB()->WriteBuffer(29, 12, "▶게임시작");
		
		SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE);
		System::getInstance()->GetDB()->WriteBuffer(51, 12, "게임종료");
		break;

	case MENU_EXIT:
		SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE);
		System::getInstance()->GetDB()->WriteBuffer(31, 12, "게임시작");

		SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), YELLOW);
		System::getInstance()->GetDB()->WriteBuffer(49, 12, "▶게임종료");	

		break;
	}

}

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}
