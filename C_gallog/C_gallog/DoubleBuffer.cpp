#include "DoubleBuffer.h"

DoubleBuffer::DoubleBuffer()
{
    m_BufferIndex = 0;
}

HANDLE DoubleBuffer::GetBuffer()
{
    return m_hBuffer[m_BufferIndex];
}

void DoubleBuffer::CreateBuffer(const int& width, const int& height)
{
    CONSOLE_CURSOR_INFO cci;
    COORD size = { width, height };
    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = width - 1;
    rect.Bottom = height - 1;

    m_hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleScreenBufferSize(m_hBuffer[0], size);
    SetConsoleWindowInfo(m_hBuffer[0], TRUE, &rect);

    m_hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleScreenBufferSize(m_hBuffer[1], size);
    SetConsoleWindowInfo(m_hBuffer[1], TRUE, &rect);

    cci.dwSize = 1;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(m_hBuffer[0], &cci);
    SetConsoleCursorInfo(m_hBuffer[1], &cci);
}

void DoubleBuffer::WriteBuffer(int x, int y, const char* string)
{
    DWORD dw;
    COORD coord = { x,y };

    SetConsoleCursorPosition(m_hBuffer[m_BufferIndex], coord);
    WriteFile(m_hBuffer[m_BufferIndex], string, strlen(string), &dw, NULL);
}

void DoubleBuffer::FlippingBuffer()
{
    SetConsoleActiveScreenBuffer(m_hBuffer[m_BufferIndex]);
    m_BufferIndex = !m_BufferIndex;
}

void DoubleBuffer::ClearBuffer()
{
    COORD coord = { 0,0 };
    DWORD dw;
    
    //SetConsoleTextAttribute(m_hBuffer[m_BufferIndex], WHITE | BLACK << 4);
    FillConsoleOutputCharacter(m_hBuffer[m_BufferIndex], ' ', CONSOLE_WIDTH * CONSOLE_HEIGHT, coord, &dw);
}

void DoubleBuffer::DestroyBuffer()
{
    CloseHandle(m_hBuffer[0]);
    CloseHandle(m_hBuffer[1]);
}

bool DoubleBuffer::CloseHandle(HANDLE& handle)
{
    if (INVALID_HANDLE_VALUE != handle)
    {
        __try
        {
            return (0 !=::CloseHandle(handle));    
        }

        __finally
        {
            handle = INVALID_HANDLE_VALUE;
        }
    }

    return false;
}



DoubleBuffer::~DoubleBuffer()
{
}
