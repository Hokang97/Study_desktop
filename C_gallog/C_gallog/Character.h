#pragma once
#include "Object.h"
#include "Bullet.h"

class Character : public Object
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(float dt);
	virtual void Destroy();

	vector<Bullet>& GetBullet();
private:
	int mChar[5][5] =
	{ {1,1,1,0,0},
	  {1,0,0,0,0} ,
	  {1,1,1,1,1} ,
	  {1,0,0,0,0} ,
	  {1,1,1,0,0} };

	vector<Bullet> m_bullet;

	INT mBulletDealy = 0;
public:
	Character();
	~Character();

};

