#include "Enemy.h"

void Enemy::SetBullet(vector<Bullet>& bullet)
{
	m_pBullet = &bullet;
}

void Enemy::Init()
{
	m_MoveTime = GetTickCount();
}

void Enemy::Update(float dt)
{
	if (System::getInstance()->GetCollision()) return;
	if (m_Remove) return;

	if (GetTickCount() - m_MoveTime > 100)
	{
		m_MoveTime = GetTickCount();
		posX--;
	}

	if (posX < 2)
	{
		System::getInstance()->SetCollision(TRUE);
		Destroy();
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(m_pBullet != nullptr)
			for (auto itor = m_pBullet->begin(); itor != m_pBullet->end(); ++itor)
			{
				if (mChar[j][i] && j + posX == itor->GetPosX() && i + posY == itor->GetPosY())
				{
					int score = System::getInstance()->GetScore();
					System::getInstance()->SetScore(score + 1);

					itor->m_Remove = TRUE;
					Destroy();
					return;
				}
			}
		}
	}

	
}

void Enemy::Render(float dt)
{
	if (m_Remove) return;

	if (posX > 2)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int DrawX = (posX + j) * 2;
				int DrawY = posY + i;

				if(DrawX > 1 && DrawX < 84 && DrawY > 3 && DrawY < 22)
				System::getInstance()->GetDB()->WriteBuffer((posX + j) * 2, (posY + i), mChar[i][j] ? "бс" : "");
			}
		}
	}
	
}

void Enemy::Destroy()
{
	m_Remove = TRUE;
}



Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
