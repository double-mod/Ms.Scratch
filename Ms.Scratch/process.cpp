#include "process.h"
#include "drawutil.h"
#include "input.h"
#include "stage.h"
#include "animation.h"
#include "sound.h"
//************************************
//グローバル変数
//***********************************
static LPDIRECT3D9			   g_pD3D = NULL;					//Direct3Dオブジェクト
static LPDIRECT3DDEVICE9	   g_pD3DDevice = NULL;		//Deviceオブジェクト
static LPDIRECT3DTEXTURE9	   g_tex = NULL;
static stage Stage;
static animation Anime;
static int status = MENU;
static bool b = true;

INT WINAPI G_PLUS(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW),
		NULL,
		CLASS_NAME,
		NULL
	};

	HWND hWnd;	//handle of window
	MSG msg;	//message box

	RegisterClassEx(&wcex);

	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);

	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Update();
			Draw();
		}
	}

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	timeEndPeriod(1);

	Uninit();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "終了しますか？", "終了", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_CLOSE:
		nID = MessageBox(hWnd, "終了しますか？", "終了", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = bWindow;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (bWindow)
	{
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			return E_FAIL;
		}
	}

	//アルファブレンド
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	InitInput(hInstance, hWnd);
	Stage.stageInit(g_pD3DDevice);
	Anime.init(g_pD3DDevice);
	InitSound(hWnd);
	PlaySound(SOUND_LABEL_TITLE);
	return S_OK;
}

void Uninit(void)
{
	UninitSound();
	UninitInput();

	if (g_tex) {
		g_tex->Release();
		g_tex = NULL;
	}

	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}

void Update(void)
{
	UpdateInput();
	switch (status)
	{
	case MENU:
		Anime.update();
		break;
	case GAME:
		if (GetKeyboardTrigger(DIK_LCONTROL))
		{
			Anime.setTime0();
			Anime.setAnime(TITLE);
			status = MENU;
		}
		Anime.update();
		if(b)	
			Stage.stageUpdate();
		break;
	default:
		Anime.update();
		Stage.stageUpdate();
	}

}

void Draw(void)
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		switch (status)
		{
		case MENU:
		{
			Anime.titledraw(g_pD3DDevice);
			if (Anime.getAnime() == CLEAR)
			{
				status = GAME;
			}
			break;
		}
		case GAME:
		{
			static int time = 0;
			static bool a = false;
			if (!a)
			{
				if (Anime.configDraw(g_pD3DDevice))
					a = !a;
			}
			else
			{
				if (Stage.currentStage() == BONUS1 && !b)
				{
					if (Anime.shootConfig(g_pD3DDevice))
					{
						b = !b;
					}
				}
				else
				{
					Stage.stageDraw(g_pD3DDevice);
					if (Stage.nextCheck())
					{
						if (!Anime.getClearStat())
						{
							Anime.clearDraw(g_pD3DDevice);
						}
						else
						{
							Stage.setNextstage(false);
							Stage.goNextStage();
							if (Stage.currentStage() == BONUS1)
								b = false;
							if (!Stage.endCheck())
							{
								Stage.mapInit();
							}
							else
							{
								status = END;
								a = !a;
								Anime.setTime0();
							}
							Anime.setClearStat(false);
						}
					}
				}
			}
			break;
		}
		case END:
		{
			Anime.endDraw(g_pD3DDevice);
			if (Anime.getAnime() == FINAL)
			{
				status = MENU;
				Anime.setTime0();
				Stage.goBackToHead();
				Stage.mapInit();
			}
			break;
		}
		}
		g_pD3DDevice->EndScene();
		g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}