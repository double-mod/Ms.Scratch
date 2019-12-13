#pragma once
#ifndef _PROCESS_H
#define _PROCESS_H

#define CLASS_NAME "AppClass"
#define WINDOW_NAME "G++"

//*********************************
//インクルードファイル
//*********************************
#include <windows.h>
#include "d3dx9.h"		
#include "Dinput.h"

//**********************************
//ライブラリのリンク 
//*********************************
#if 1
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#endif

//************************************
//マクロ定義
//*************************************
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (800)

enum
{
	MENU,
	GAME,
	FINAL,
};

INT WINAPI G_PLUS(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void Uninit(void);
void Update(void);
void Draw(void);


#endif // !_PROCESS_H
