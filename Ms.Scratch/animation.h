#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include "drawutil.h"

enum
{
	TITLE,
	CLEAR,
	END
};


class animation
{
public:
	bool init(LPDIRECT3DDEVICE9	dev);
	void update();
	void draw(LPDIRECT3DDEVICE9	dev);
	void clearDraw(LPDIRECT3DDEVICE9	dev);
	void titledraw(LPDIRECT3DDEVICE9	dev);
	bool configDraw(LPDIRECT3DDEVICE9	dev);
	bool shootConfig(LPDIRECT3DDEVICE9	dev);
	void endDraw(LPDIRECT3DDEVICE9	dev);
	bool screenmatDraw(LPDIRECT3DDEVICE9    dev);
	int getAnime() { return anime_select; };
	bool getClearStat() { return clear_over; }
	void setClearStat(const bool& i) { clear_over = i; }
	void setAnime(const int&);
	void setTime0() { time = 0; }
private:
	unsigned time = 0;
	int anime_select = TITLE;
	bool clear_over = false;
};	

#endif // !ANIMATION_H
