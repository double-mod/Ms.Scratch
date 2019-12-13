#pragma once
#ifndef _DRAWUTIL_H
#define _DRAWUTIL_H

#include <d3dx9.h>

#define TILE_SIZE 40

typedef struct {
	D3DXVECTOR3 pos;//�X�N���[�����W
	float rhw;//���1.0
	D3DCOLOR col;//���_�J���[
	float u, v;
}VERTEX_2D;

void DrawQuad(
	float x,
	float y,
	LPDIRECT3DDEVICE9 dev,
	LPDIRECT3DTEXTURE9 tex);

void DrawQuad(
	float x,
	float y,
	float w,
	float h,
	LPDIRECT3DDEVICE9 dev,
	LPDIRECT3DTEXTURE9 tex);


void DrawQuad(
	float x,
	float y,
	float w,
	float h,
	int u,
	LPDIRECT3DDEVICE9 dev,
	LPDIRECT3DTEXTURE9 tex);


#endif // !_DRAWUTIL_H
