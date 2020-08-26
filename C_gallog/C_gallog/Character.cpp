#include "Character.h"

void Character::Init()
{
	posX = 3;
	posY = 3;
}

void Character::Update(float dt)
{
	Sleep(20);
	if (GetAsyncKeyState(VK_UP))
	{
		if (posY > 3) posY--;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (posY < 17) posY++;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (posX > 3) posX--;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (posX < 36) posX++;
	}

	if (GetAsyncKeyState(VK_SPACE) && GetTickCount() - mBulletDealy > 100)
	{
		mBulletDealy = GetTickCount();

		Bullet temp;
		temp.SetPosX(posX + 5);
		temp.SetPosY(posY + 2);
		m_bullet.push_back(temp);
	}

	for (auto itor = m_bullet.begin(); itor != m_bullet.end();)
	{
		if (itor->m_Remove)
			itor = m_bullet.erase(itor);
		else
		{
			itor->Update(dt);
			itor++;
		}
	}
}

void Character::Render(float dt)
{
	SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			System::getInstance()->GetDB()->WriteBuffer((posX + j) * 2, (posY + i), mChar[i][j] ? "бс" : "");
		}
	}

	for (auto itor = m_bullet.begin(); itor != m_bullet.end(); ++itor)
		itor->Render(dt);

}

void Character::Destroy()
{
	for (auto itor = m_bullet.begin(); itor != m_bullet.end();)
		itor->Destroy();
}

vector<Bullet>& Character::GetBullet()
{
	return m_bullet;
}

Character::Character()
{
}

Character::~Character()
{
}
