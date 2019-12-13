#include "Box.h"
#include <iostream>
#include "input.h"

using namespace std;

//左値 noun definition
void Left_N::update(Box& box)
{
	cout << prop.first << endl;
	for (auto i : prop.second)
	{
		cout << i<<" ";
	}
}

//右値　adj definition
void Right_Adj::update(Box& box)
{
	cout << prop.first << endl;
	for (auto i : prop.second)
	{
		cout << i << " ";
	}
}

//picture definition
void Pic::update(Box& box)
{
	cout << prop.first << endl;
	for (auto i : prop.second)
	{
		cout << i << " ";
	}
}

//「は」definition
void Def::update(Box& box)
{
	cout << prop.first << endl;
	for (auto i : prop.second)
	{
		cout << i << " ";
	}
}

int entity(const int& x)
{
	if (x >= 0 && x < 256)
		return isLeft;
	else if (x >= 256 && x < 512)
		return isPicture;
	else if (x >= 512 && x < 768)
		return isRight;
	else if (x >= 768 && x < 1024)
		return isCommand;
}

bool findfunc(std::pair<BoxId, FuncId>& prop,const int& func)
{
	for (auto a : prop.second)
	{
		if (a == func)
			return true;
	}
	return false;
}


