#include "GameDefine.h"
#include "SceneDefine.h"
#include "System.h"
#pragma warning(disable:4996)
System* System::_instance = nullptr;
void Init();

int main()
{
	Init();
	
	while (!System::getInstance()->GetExit())
	{	
		System::getInstance()->GetDB()->ClearBuffer();


		System::getInstance()->GetSM()->Render(DELTATIME);
		System::getInstance()->GetSM()->Update(DELTATIME);

		
		System::getInstance()->GetDB()->FlippingBuffer();
	}

	System::getInstance()->GetDB()->DestroyBuffer();
	return 0;
}

void Init()
{
	System::getInstance()->GetDB()->CreateBuffer(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	System::getInstance()->GetSM()->RegisterScene("MenuScene", new MenuScene);
	System::getInstance()->GetSM()->RegisterScene("GameScene", new GameScene);

	System::getInstance()->GetSM()->reserveChangeScene("MenuScene");
}