#pragma once
#ifndef _STAGE_H
#define _STAGE_H

#include "d3dx9.h"	
#include "Box.h"
#include <vector>

#define MAP_X 20
#define MAP_Y 20

static std::vector<LPDIRECT3DTEXTURE9>  tex_left;

static std::vector<LPDIRECT3DTEXTURE9>  tex_right;

static std::vector<LPDIRECT3DTEXTURE9>  tex_picture;

static std::vector<LPDIRECT3DTEXTURE9>  tex_def;

static std::vector<LPDIRECT3DTEXTURE9>  tex_background;

static std::vector<LPDIRECT3DTEXTURE9>  tex_amelie;

static LPDIRECT3DTEXTURE9  tex;

static std::pair<BoxId, FuncId> map[MAP_Y][MAP_X];

static Box* test[MAP_Y][MAP_X];

enum
{
	MAP1,
	MAP2,
	MAP3,
	MAP4,
	MAP5,
	MAP6,
	MAP7,
	MAP8,
	BONUS1,
	MAPEND
};

struct InputInfo
{
	std::pair<BoxId, FuncId> map[MAP_Y][MAP_X];
	std::vector<Box*> elements;
};

class stage
{
public:
	bool stageInit(LPDIRECT3DDEVICE9	dev);
	bool textureInit(LPDIRECT3DDEVICE9	dev);
	void mapInit();
	void stageUpdate();
	void stageDraw(LPDIRECT3DDEVICE9 dev);
	void memoryReset();
	void setNextstage(const bool&);
	bool nextCheck() { return next_stage; }
	void goNextStage() { if (current_map < BONUS1)current_map++; else { end = true; current_map = MAP1; } }
	void goBackToHead() { end=false; }
	int currentStage() { return current_map; }
	bool endCheck() { return end; }
	int stageInput();
	std::vector<Box*> elements;
private:
	int current_map = MAP1;
	bool next_stage = false;
	bool end = false;
};

Box* createBox(unsigned i);
bool norepeat(FuncId&,BoxId&);
void remove(Pos&, std::vector<Box*>&,const int&);
#endif // !_STAGE_H
