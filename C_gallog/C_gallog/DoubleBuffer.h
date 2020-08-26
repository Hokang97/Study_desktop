#pragma once
#include <conio.h>
#include <Windows.h>
#include "GameDefine.h"

class DoubleBuffer
{
public:
	HANDLE GetBuffer();

	void CreateBuffer(const int& width, const int& height);
	void WriteBuffer(int x, int y, const char* string);
	void FlippingBuffer();
	void ClearBuffer();
	void DestroyBuffer();
	
	bool CloseHandle(HANDLE& handle);

private:
	int m_BufferIndex;
	HANDLE m_hBuffer[2];


public:
	DoubleBuffer();
	~DoubleBuffer();

};

