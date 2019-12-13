#include "animation.h"
#include "drawutil.h"
#include "input.h"
#include "process.h"
#include <vector>
#include "sound.h"

using namespace std;

const char* fend[]
{
	{ "texture/end/end0.png" },
	{ "texture/end/end1.png" },
	{ "texture/end/end2.png" },
	{ "texture/end/end3.png" },
	{"0"}
};

const char* ftitle[]
{
	{ "texture/title/title0.png" },
	{ "texture/title/title1.png" },
	{ "texture/title/title2.png" },
	{ "texture/title/title3.png" },
	{ "texture/title/title4.png" },
	{ "texture/title/screenmat.png" },
	{ "texture/title/start1.png" },
	{ "texture/title/start2.png" },
	{ "texture/title/team1.png" },
	{ "texture/title/team2.png" },
	{ "texture/title/config.png" },
	{ "texture/title/j.png" },
	{ "0" }
};

const char* fclear[]
{
	{ "texture/clear/clear0.png" },
	{ "texture/clear/clear1.png" },
	{"0"}
};

static LPDIRECT3DTEXTURE9  tex;

static std::vector<LPDIRECT3DTEXTURE9>  tex_title;

static std::vector<LPDIRECT3DTEXTURE9>  tex_clear;

static std::vector<LPDIRECT3DTEXTURE9>  tex_end;

bool animation::init(LPDIRECT3DDEVICE9	dev)
{
	HRESULT hr;
	//menu
	for (size_t i = 0; ftitle[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			ftitle[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_title.push_back(tex);
	}
	//clear
	for (size_t i = 0; fclear[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			fclear[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_clear.push_back(tex);
	}
	//end
	for (size_t i = 0; fend[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			fend[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_end.push_back(tex);
	}
}

void animation::update()
{
	if (time++ < 2000)
		;
	else
		time = 500;
}

void animation::draw(LPDIRECT3DDEVICE9	dev)
{
	titledraw(dev);
	//clearDraw(dev);
}

void animation::titledraw(LPDIRECT3DDEVICE9	dev)
{
	static int a=1;
	if (time < 20)
	{
		DrawQuad(0, 0, 800, 800, 0, dev, tex_title[8]);
	}
	else if (time < 40)
	{
		DrawQuad(0, 0, 800, 800, 80, dev, tex_title[8]);
	}
	else if (time < 60)
	{
		DrawQuad(0, 0, 800, 800, 160, dev, tex_title[8]);
	}
	else if (time < 80)
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_title[8]);
	}
	else if (time < 100)
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_title[9]);
	}
	else if (time < 120)
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_title[9]);
	}
	else if (time < 140)
	{
		DrawQuad(0, 0, 800, 800, 160, dev, tex_title[9]);
	}
	else if (time < 160)
	{
		DrawQuad(0, 0, 800, 800, 80, dev, tex_title[9]);
	}
	else if (time < 180)
	{
		DrawQuad(0, 0, 800, 800, 0, dev, tex_title[9]);
	}
	else if (time < 200)
	{
		DrawQuad(0, 0, 800, 800, 0, dev, tex_title[0]);
	}
	else if (time < 220)
	{
		DrawQuad(0, 0, 800, 800, 80, dev, tex_title[0]);
	}
	else if (time < 240)
	{
		DrawQuad(0, 0, 800, 800, 160, dev, tex_title[0]);
	}
	else if (time < 260)
	{
		DrawQuad(0, 0, 800, 800, 240, dev, tex_title[0]);
	}
	else if (time < 270)
	{
		DrawQuad(0, 0, 800, 800, dev, tex_title[1]);
	}
	else if (time < 280)
	{
		DrawQuad(0, 0, 800, 800, dev, tex_title[2]);
	}
	else if (time < 290)
	{
		DrawQuad(0, 0, 800, 800, dev, tex_title[3]);
	}
	else if (time < 300)
	{
		DrawQuad(0, 0, 800, 800, dev, tex_title[4]);
	}
	else
	{
		DrawQuad(0, 0, 800, 800, dev, tex_title[4]);
		static bool shift = true;
		if (shift)
		{
			if (time % 30 == 0)
				shift = !shift;
			DrawQuad(200, 380, 400, 60, dev, tex_title[6]);
		}
		else
		{
			if (time % 30 == 0)
				shift = !shift;
			DrawQuad(200, 380, 400, 60, dev, tex_title[7]);
		}

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			setAnime(CLEAR);
			StopSound();
			PlaySound(SOUND_LABEL_GAME);
			time = 0;
		}
	}
}

void animation::clearDraw(LPDIRECT3DDEVICE9	dev)
{
	static bool shift = false;
	static int round = 0;

	if (round == 0)
	{
		setClearStat(false);
	}
	if (round++ < 150)
	{
		if(time % 30 == 0)
			shift = !shift;
	}
	else
	{
		setClearStat(true);
		round = 0;
	}
	if (shift)
	{
		DrawQuad(0, 0, 800, 800, dev, tex_clear[0]);
	}
	else
		DrawQuad(0, 0, 800, 800, dev, tex_clear[1]);
}

bool animation::screenmatDraw(LPDIRECT3DDEVICE9    dev)
{
	static int i = -800;
	static int change = 15;
	static char wait = 0;
	DrawQuad(0, i, 800, 800, dev, tex_title[5]);
	if (i < 0)
		;
	else if (wait < 10)
	{
		change = 0;
		wait++;
	}
	else
	{
		change = -10;
		wait = 0;
	}
	i+=change;
	if (i < -800)
	{
		change = 15;
		return false;
	}
	return true;
}

void animation::setAnime(const int&i)
{
	anime_select = i;
}

void animation::endDraw(LPDIRECT3DDEVICE9	dev)
{
	if (time < 20)
	{
		DrawQuad(0, 0, 800, 800, 0, dev, tex_end[1]);
		DrawQuad(0, 0, 800, 800, 0, dev, tex_end[2]);
	}
	else if (time < 40)
	{
		DrawQuad(0, 0, 800, 800, 80, dev, tex_end[1]);
		DrawQuad(0, 0, 800, 800, 80, dev, tex_end[2]);
	}
	else if (time < 60)
	{
		DrawQuad(0, 0, 800, 800, 160, dev, tex_end[1]);
		DrawQuad(0, 0, 800, 800, 160, dev, tex_end[2]);
	}
	else if (time < 80)
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_end[1]);
		DrawQuad(0, 0, 800, 800, 255, dev, tex_end[2]);
	}
	else
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_end[1]);
		DrawQuad(0, 0, 800, 800, 255, dev, tex_end[2]);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			setAnime(FINAL);
			StopSound();
			PlaySound(SOUND_LABEL_TITLE);
			time = 0;
		}
	}
}

bool animation::configDraw(LPDIRECT3DDEVICE9	dev)
{
	if (time < 20)
	{
		DrawQuad(0, 0, 800, 800, 0, dev, tex_title[10]);
	}
	else if (time < 40)
	{
		DrawQuad(0, 0, 800, 800, 80, dev, tex_title[10]);
	}
	else if (time < 60)
	{
		DrawQuad(0, 0, 800, 800, 160, dev, tex_title[10]);
	}
	else if (time < 80)
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_title[10]);
	}
	else
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_title[10]);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			return true;
		}
		return false;
	}
	return false;
}

bool animation::shootConfig(LPDIRECT3DDEVICE9	dev)
{
	if (time < 20)
	{
		DrawQuad(0, 0, 800, 800, 0, dev, tex_title[11]);
	}
	else if (time < 40)
	{
		DrawQuad(0, 0, 800, 800, 80, dev, tex_title[11]);
	}
	else if (time < 60)
	{
		DrawQuad(0, 0, 800, 800, 160, dev, tex_title[11]);
	}
	else if (time < 80)
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_title[11]);
	}
	else
	{
		DrawQuad(0, 0, 800, 800, 255, dev, tex_title[11]);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			return true;
		}
		return false;
	}
	return false;
}