#include <stdio.h>

#include "Platform/Api.h"
#include "Platform/Win/Win.h"


//----- (00462C94) --------------------------------------------------------
int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hprevinstance, wchar_t *lpCmdLine, int nShowCmd)
{
	extern bool MM_Main(const wchar_t *pCmdLine);
	return MM_Main(lpCmdLine) != false;
}


void OS_MsgBox(const wchar_t *msg, const wchar_t *title)
{
    MessageBoxW(nullptr, msg, title, 0);
}



void OS_PeekMessage()
{
    MSG msg;
    if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            extern void Engine_DeinitializeAndTerminate(int exit_code);
            Engine_DeinitializeAndTerminate(0);
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}


unsigned int OS_GetTime()
{
    return GetTickCount();
}

unsigned __int64 OS_GetPrecisionTime()
{
    return timeGetTime();
}


bool OS_IfShiftPressed()
{
    return GetAsyncKeyState(VK_SHIFT) >= 0;
}

bool OS_IfCtrlPressed()
{
    return GetAsyncKeyState(VK_CONTROL);
}

void OS_ShowCursor(bool show)
{
    ShowCursor(show ? 1 : 0);
}


void OS_PeekMessageLoop()
{
    MSG msg;
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            extern void Engine_DeinitializeAndTerminate(int);
            Engine_DeinitializeAndTerminate(0);
        }

        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

void OS_WaitMessage()
{
    WaitMessage();
}


void OS_Sleep(int ms)
{
    Sleep(ms);
}

Point OS_GetMouseCursorPos()
{
    POINT pt;
    GetCursorPos(&pt);

    return Point(pt.x, pt.y);
}


bool OS_OpenConsole()
{
    if (AllocConsole())
    {
        freopen("conin$", "r", stdin);
        freopen("conout$", "w", stdout);
        freopen("conout$", "w", stderr);

        return true;
    }

    return false;
}