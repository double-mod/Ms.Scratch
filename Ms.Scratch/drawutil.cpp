#include "drawutil.h"

void DrawQuad(
	float x,
	float y,
	LPDIRECT3DDEVICE9 dev,
	LPDIRECT3DTEXTURE9 tex)
{
	VERTEX_2D Vertex[4];

	Vertex[0].pos = { x * TILE_SIZE, y * TILE_SIZE,0.0f };
	Vertex[1].pos = { x * TILE_SIZE + TILE_SIZE,y * TILE_SIZE,0.0f };
	Vertex[2].pos = { x * TILE_SIZE,y * TILE_SIZE + TILE_SIZE,0.0f };
	Vertex[3].pos = { x * TILE_SIZE + TILE_SIZE,y * TILE_SIZE + TILE_SIZE,0.0f };

	Vertex[0].u = 0.0;
	Vertex[0].v = 0.0;
	Vertex[1].u = 1.0;
	Vertex[1].v = 0.0;
	Vertex[2].u = 0.0;
	Vertex[2].v = 1.0;
	Vertex[3].u = 1.0;
	Vertex[3].v = 1.0;

	Vertex[0].rhw = Vertex[1].rhw = Vertex[2].rhw = Vertex[3].rhw = 1.0f;
	Vertex[0].col = Vertex[1].col = Vertex[2].col = Vertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	dev->SetFVF(
		D3DFVF_XYZRHW |
		D3DFVF_DIFFUSE |
		D3DFVF_TEX1);

	dev->SetTexture(0,
		tex);

	dev->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2,
		Vertex,
		sizeof(VERTEX_2D));
}

void DrawQuad(
	float x,
	float y,
	float w,
	float h,
	LPDIRECT3DDEVICE9 dev,
	LPDIRECT3DTEXTURE9 tex)
{
	VERTEX_2D Vertex[4];

	Vertex[0].pos = { x ,y ,0.0f };
	Vertex[1].pos = { x + w ,y ,0.0f };
	Vertex[2].pos = { x ,y + h ,0.0f };
	Vertex[3].pos = { x + w ,y + h ,0.0f };

	Vertex[0].u = 0.0;
	Vertex[0].v = 0.0;
	Vertex[1].u = 1.0;
	Vertex[1].v = 0.0;
	Vertex[2].u = 0.0;
	Vertex[2].v = 1.0;
	Vertex[3].u = 1.0;
	Vertex[3].v = 1.0;

	Vertex[0].rhw = Vertex[1].rhw = Vertex[2].rhw = Vertex[3].rhw = 1.0f;
	Vertex[0].col = Vertex[1].col = Vertex[2].col = Vertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	dev->SetFVF(
		D3DFVF_XYZRHW |
		D3DFVF_DIFFUSE |
		D3DFVF_TEX1);

	dev->SetTexture(0,
		tex);

	dev->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2,
		Vertex,
		sizeof(VERTEX_2D));
}

void DrawQuad(
	float x,
	float y,
	float w,
	float h,
	int u,
	LPDIRECT3DDEVICE9 dev,
	LPDIRECT3DTEXTURE9 tex)
{
	VERTEX_2D Vertex[4];

	Vertex[0].pos = { x ,y ,0.0f };
	Vertex[1].pos = { x + w ,y ,0.0f };
	Vertex[2].pos = { x ,y + h ,0.0f };
	Vertex[3].pos = { x + w ,y + h ,0.0f };

	Vertex[0].u = 0.0;
	Vertex[0].v = 0.0;
	Vertex[1].u = 1.0;
	Vertex[1].v = 0.0;
	Vertex[2].u = 0.0;
	Vertex[2].v = 1.0;
	Vertex[3].u = 1.0;
	Vertex[3].v = 1.0;

	Vertex[0].rhw = Vertex[1].rhw = Vertex[2].rhw = Vertex[3].rhw = 1.0f;
	Vertex[0].col = Vertex[1].col = Vertex[2].col = Vertex[3].col = D3DCOLOR_RGBA(u, u, u, 255);

	dev->SetFVF(
		D3DFVF_XYZRHW |
		D3DFVF_DIFFUSE |
		D3DFVF_TEX1);

	dev->SetTexture(0,
		tex);

	dev->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2,
		Vertex,
		sizeof(VERTEX_2D));
}