#pragma once
#include "DoubleBuffer.h"
#include "SceneManager.h"

class System
{
public:	
	static System* getInstance()
	{
		if (_instance == nullptr)
			_instance = new System;

		return _instance;
	}	

	void Destroy()
	{
		if (m_pDB != nullptr) delete m_pDB;
		if (m_pSM != nullptr) delete m_pSM;
		if (_instance != nullptr) delete _instance;
	}

	void SetExit(BOOL done) { gameExit = done; }
	BOOL GetExit() { return gameExit; }

	void SetCollision(BOOL done) { gameCollision = done; }
	BOOL GetCollision() { return gameCollision; }

	void SetScore(SHORT value) { gameScore = value; }
	SHORT GetScore() { return gameScore; }


	DoubleBuffer* GetDB() { if (m_pDB == nullptr) m_pDB = new DoubleBuffer; return m_pDB; }
	SceneManager* GetSM() { if (m_pSM == nullptr) m_pSM = new SceneManager; return m_pSM; }

	

private:
	static System* _instance;
	SceneManager* m_pSM = nullptr;
	DoubleBuffer* m_pDB = nullptr;
	BOOL gameExit = FALSE;
	BOOL gameCollision = FALSE;
	SHORT gameScore = 0;
};

