#pragma once
#ifndef _BOX_H
#define _BOX_H

#include <vector>
#include <memory>

typedef unsigned int BoxId ;
typedef std::vector<int> FuncId ;
extern bool flg_win;

//noun		(0~255)
//picture	(256~512)
//function	(512~767)
//command	(768~1023)
enum LeftList
{
	SUNNY=0,
	FLAG,
	ROCK,
	GRASS,
	WALL,
	WATER,
	BONE,
	GUN,
	HAT
};

enum PicList
{
	P_SUNNY=256,
	P_FLAG,
	P_ROCK,
	P_GRASS,
	P_WALL,
	P_WATER,
	P_BONE,
	P_BULLET,
	P_HAT
};

enum RightList
{
	YOU = 512,
	WIN,
	MOVE,
	STOP,
	PUSH,
	SINK,
	KILL,
	SHOOT,
	GOUP
};

enum Command
{
	IS=768,
	AND
};

enum direction
{
	STAY,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BULLET
};

enum state
{
	isLeft,
	isPicture,
	isRight,
	isCommand
};

int entity(const int& x);

struct Pos
{
	int x;
	int y;
};
//=========================
//root class
//=========================
class Box
{
public:
	std::pair<BoxId, FuncId> prop;
	Pos pos;
	Box() = default;
	Box(BoxId& boxId) { prop.first = boxId; prop.second.push_back(PUSH);}
	virtual void update(Box& box) = 0;
	virtual bool isLeft() { return 0; }
	virtual bool isRight() { return 0; }
};

//左値 noun definition
class Left_N :public Box
{
public:
	Left_N() = default;
	Left_N(BoxId& boxId) :Box(boxId) {}
	virtual void update(Box& box)override;
	virtual bool isLeft() override{ return 1; } 
};

//右値　adj definition
class Right_Adj :public Box
{
public:
	Right_Adj() = default;
	Right_Adj(BoxId& boxId) :Box(boxId) {}
	virtual void update(Box& box)override;
	virtual bool isRight() override { return 1; }
};

//picture definition
class Pic :public Left_N
{
public:
	Pic(BoxId& boxId) :Left_N(boxId) { std::vector<int>().swap(prop.second); }
	virtual void update(Box& box)override;
	virtual bool isLeft() override { return 0; }
};

//「は」definition
class Def :public Box
{
public:
	Def(BoxId& boxId):Box(boxId) {}
	virtual void update(Box& box)override;
};

bool findfunc(std::pair<BoxId, FuncId>&,const int&);


//=============================
//component item
//entrance of update components
//=============================
//class UpdateComponent
//{
//public:
//	virtual ~UpdateComponent() {};
//	virtual void update(Box&) = 0;
//};
//
////push update
//class input :public UpdateComponent
//{
//public:
//	void update(Box&) override;
//};
//
//class win:public UpdateComponent
//{
//public:
//	void update(Box&) override;
//};

#endif // !_BOX_H
