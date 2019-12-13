#define _CRT_SECURE_NO_WARNINGS

#include "stage.h"
#include "drawutil.h"
#include <algorithm>
#include "input.h"
#include "process.h"

using namespace std;

static std::pair<BoxId, FuncId> null_elem;

static vector<InputInfo> inputList;

static bool next_stage = false;

const char* fleft[]
{
	{ "texture/left/sunny.png" },
	{ "texture/left/flag.png" },
	{ "texture/left/rock.png" },
	{ "texture/left/grass.png" },
	{ "texture/left/wall.png" },
	{ "texture/left/water.png" },
	{ "texture/left/bone.png" },
	{ "texture/left/bullet.png" },
	{ "texture/left/hat.png" },
	{ "0" }
};

const char* fpicture[]
{
	{ "texture/pic/p_sunny.png" },
	{ "texture/pic/p_flag.png" },
	{ "texture/pic/p_rock.png" },
	{ "texture/pic/p_grass.png" },
	{ "texture/pic/p_wall.png" },
	{ "texture/pic/p_water.png" },
	{ "texture/pic/p_bone.png" },
	{ "texture/pic/p_bullet.png" },
	{ "texture/pic/p_hat.png" },
	{ "0" }
};

const char* fright[]
{
	{ "texture/right/input.png" },
	{ "texture/right/win.png" },
	{ "texture/right/move.png" },
	{ "texture/right/stop.png" },
	{ "texture/right/push.png" },
	{ "texture/right/sink.png" },
	{ "texture/right/kill.png" },
	{ "texture/right/shoot.png" },
	{ "texture/right/up.png" },
	{ "0" }
};

const char* fdef[]
{
	{ "texture/def/is.png" },
	{ "0" }
};

const char* fbackground[]
{
	{ "texture/background/background1.jpg" },
	{ "texture/background/background2.jpg" },
	{ "texture/background/background3.jpg" },
	{ "texture/background/background4.jpg" },
	{ "texture/background/background5.jpg" },
	{ "texture/background/background6.jpg" },
	{ "texture/background/background7.jpg" },
	{ "texture/background/background8.jpg" },
	{ "texture/background/background9.jpg" },
	{ "0" }
};

const char* famelie[]
{
	{ "texture/amelie/down1.png" },
	{ "texture/amelie/down2.png" },
	{ "texture/amelie/water1.png" },
	{ "texture/amelie/water2.png" },
	{ "texture/amelie/enemy1.png" },
	{ "texture/amelie/enemy2.png" },
	{ "0" }
};

const char* map_data[]
{
	{ "map/map1.txt" },
	{ "map/map2.txt" },
	{ "map/map3.txt" },
	{ "map/map4.txt" },
	{ "map/map5.txt" },
	{ "map/map6.txt" },
	{ "map/map7.txt" },
	{ "map/map8.txt" },
	{ "map/bonus1.txt" },
	{ "0" }
};

bool stage::textureInit(LPDIRECT3DDEVICE9	dev)
{
	HRESULT hr;
	//left
	for (size_t i = 0; fleft[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			fleft[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_left.push_back(tex);
	}
	//right
	for (size_t i = 0; fright[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			fright[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_right.push_back(tex);
	}
	//picture
	for (size_t i = 0; fpicture[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			fpicture[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_picture.push_back(tex);
	}
	//def
	for (size_t i = 0; fdef[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			fdef[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_def.push_back(tex);
	}
	//background
	for (size_t i = 0; fbackground[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			fbackground[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_background.push_back(tex);
	}
	//amelie
	for (size_t i = 0; famelie[i] != "0"; i++)
	{
		hr = D3DXCreateTextureFromFile(dev,	//デバイスオブジェクト		→戻り値マクロFAILEDでチェック
			famelie[i],	//パス名に気を付ける
			&tex);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Load tex error", "load tex error", MB_OK);
			return false;
		}
		else
			tex_amelie.push_back(tex);
	}
	return true;
}

void stage::mapInit()
{
	//load map
	FILE *fp = NULL;
	int width = 0, height = 0;
	BoxId boxid;
	if ((fp = fopen(map_data[current_map], "r")) != NULL)
	{
		fscanf_s(fp, "%d,%d", &height, &width) != NULL;
		int b = 2;
		InputInfo lhs;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fscanf(fp, "%d,", &boxid);
				if (auto elem = createBox(boxid))
				{
					elem->pos.y = i;
					elem->pos.x = j;
					elements.push_back(elem);
					map[i][j] = elem->prop;
					auto lhs_elem = createBox(boxid);
					lhs_elem->pos.y = elem->pos.y;
					lhs_elem->pos.x = elem->pos.x;
					lhs.elements.push_back(lhs_elem);
					lhs.map[i][j] = map[i][j];
				}
			}
		}
		inputList.push_back(lhs);
	}
	fclose(fp);
}

void stage::memoryReset()
{
	for (size_t i = 0; i < MAP_Y; i++)
	{
		for (size_t j = 0; j < MAP_X; j++)
		{
			map[i][j] = null_elem;
		}
	}
	std::vector<Box*>().swap(elements);
	std::vector<InputInfo>().swap(inputList);
}

bool stage::stageInit(LPDIRECT3DDEVICE9	dev)
{
	if (textureInit(dev))
		mapInit();
	else
		return false;
}

void stage::stageUpdate()
{
	static int time = 1;
	static int change_x = 1, change_y = 1;
	//clear funcid turnround
	for (auto elem : elements)
	{
		if (entity(elem->prop.first) == isPicture)
		{
			vector<int>().swap(elem->prop.second);
			vector<int>().swap(map[elem->pos.y][elem->pos.x].second);
		}
	}
	//insert funcid row
	for (auto elem : elements)
	{
		//pic func insert
		if (entity(elem->prop.first) == isLeft)
		{
			//right is def
			if (map[elem->pos.y][elem->pos.x + 1].first == IS)
			{
				if (entity(map[elem->pos.y][elem->pos.x + 2].first) == isLeft || entity(map[elem->pos.y][elem->pos.x + 2].first) == isRight)
				{
					for (auto a : elements)
					{
						if ((a->prop.first - 256) == elem->prop.first)
						{
							if (map[elem->pos.y][elem->pos.x + 2] != null_elem && norepeat(a->prop.second, map[elem->pos.y][elem->pos.x + 2].first))
								a->prop.second.push_back(map[elem->pos.y][elem->pos.x + 2].first);
							if (map[elem->pos.y][elem->pos.x + 2] != null_elem && norepeat(map[a->pos.y][a->pos.x].second, map[elem->pos.y][elem->pos.x + 2].first)&&
								map[a->pos.y][a->pos.x]!=null_elem)
								map[a->pos.y][a->pos.x].second.push_back(map[elem->pos.y][elem->pos.x + 2].first);
							/*if (entity(map[elem->pos.y][elem->pos.x + 2].first) == isLeft)
							{
								a->prop.first = map[elem->pos.y][elem->pos.x + 2].first+256;
							}*/
						}
					}
				}
			}

			//down is def
			if (map[elem->pos.y + 1][elem->pos.x].first == IS)
			{
				if (entity(map[elem->pos.y + 2][elem->pos.x].first) == isLeft || entity(map[elem->pos.y + 2][elem->pos.x].first) == isRight)
				{
					for (auto a : elements)
					{
						if ((a->prop.first - 256) == elem->prop.first)
						{
							if (map[elem->pos.y + 2][elem->pos.x] != null_elem && norepeat(a->prop.second, map[elem->pos.y + 2][elem->pos.x].first))
								a->prop.second.push_back(map[elem->pos.y + 2][elem->pos.x].first);
							if (map[elem->pos.y + 2][elem->pos.x] != null_elem && norepeat(map[a->pos.y][a->pos.x].second, map[elem->pos.y + 2][elem->pos.x].first))
								map[a->pos.y][a->pos.x].second.push_back(map[elem->pos.y + 2][elem->pos.x].first);
						}
					}
				}
			}
		}
	}
	//insert funcid col
	for (auto elem : elements)
	{
		for (auto a : elem->prop.second)
		{
			if (entity(a) == isLeft)
			{
				elem->prop.first = a+256;
			}
			if (map[elem->pos.y][elem->pos.x] == null_elem)
			{
				map[elem->pos.y][elem->pos.x] = elem->prop;
			}
			if (findfunc(elem->prop, PUSH) && (!findfunc(map[elem->pos.y][elem->pos.x], PUSH)))
			{
				map[elem->pos.y][elem->pos.x].second.push_back(PUSH);
			}
		}
	}

	auto insert = stageInput();

	for (auto elem : elements)
	{
		if(findfunc(elem->prop,YOU))
		{
			Pos direction = elem->pos;
			//input update
			if (insert == UP)
			{
				direction.y--;
			}
			else if (insert == DOWN)
			{
				direction.y++;
			}
			else if (insert == LEFT)
			{
				direction.x--;
			}
			else if (insert == RIGHT)
			{
				direction.x++;
			}
			//
			if (findfunc(map[direction.y][direction.x],STOP))
			{
				;
			}
			else if (findfunc(map[direction.y][direction.x], SHOOT)&&insert==BULLET)
			{
				auto bullet = createBox(P_BULLET);
				bullet->pos.x = elem->pos.x;
				bullet->pos.y = elem->pos.y-1;
				elements.push_back(bullet);
			}
			else if (findfunc(map[direction.y][direction.x], PUSH))
			{
				Pos change;
				vector<Pos>clist{};
				bool check = true;
				int i = 1;
				change.x = direction.x - elem->pos.x;
				change.y = direction.y - elem->pos.y;
				for (; check; i++)
				{
					if (findfunc(map[direction.y + change.y * i][direction.x + change.x * i], PUSH))
					{

					}
					else if (findfunc(map[direction.y + change.y * i][direction.x + change.x * i], STOP))
					{
						check = false;
						i = -1;
						break;
					}
					else
						check = false;
				}
				for (int j = 0; j < i; j++)
				{
					Pos lhs;
					lhs.x = elem->pos.x + change.x*j;
					lhs.y = elem->pos.y + change.y*j;
					clist.push_back(lhs);
					map[lhs.y][lhs.x] = null_elem;
				}
				change.x = direction.x - elem->pos.x;
				change.y = direction.y - elem->pos.y;

				for (auto a : elements)
				{
					for (auto b : clist)
					{
						if ((findfunc(a->prop, PUSH)||findfunc(a->prop,YOU)) &&b.x == a->pos.x&&b.y == a->pos.y)
						{
							if(map[a->pos.y][a->pos.x] == a->prop)
							map[a->pos.y][a->pos.x] = null_elem;
							a->pos.x += change.x;
							a->pos.y += change.y;
							map[a->pos.y][a->pos.x] = a->prop;
							break;
						}
					}
				}
				
			}
			else if (findfunc(map[direction.y][direction.x], WIN))
			{
				memoryReset();
				if (current_map < MAPEND)
					;
				else
					current_map = MAP1;
				setNextstage(true);
				break;
			}
			else
			{
				map[elem->pos.y][elem->pos.x] = null_elem;
				map[direction.y][direction.x].first = elem->prop.first;
				for (auto b : elem->prop.second)
					map[direction.y][direction.x].second.push_back(b);
				elem->pos = direction;
			}
		}
		else if (findfunc(elem->prop, SHOOT) && insert == BULLET)
		{
			auto bullet = createBox(P_BULLET);
			bullet->pos.x = elem->pos.x;
			bullet->pos.y = elem->pos.y - 1;
			elements.push_back(bullet);
		}
		else if (findfunc(elem->prop, SINK))
		{
			for (auto a : elements)
			{
				if (a->pos.x == elem->pos.x&&a->pos.y == elem->pos.y&&(!findfunc(a->prop,SINK)))
				{
					remove(a->pos, elements,SINK);
				}
			}
		}
		else if (findfunc(elem->prop, KILL))
		{
			for (auto a : elements)
			{
				if (a->pos.x == elem->pos.x&&a->pos.y == elem->pos.y&& findfunc(a->prop, YOU))
				{
					remove(a->pos, elements,KILL);
				}
			}
		}
		else if (entity(elem->prop.first)!=isPicture&&(!findfunc(map[elem->pos.y][elem->pos.x],PUSH)))
		{
			map[elem->pos.y][elem->pos.x].second.push_back(PUSH);
		}
		if (findfunc(elem->prop, GOUP))
		{
			if (elem->pos.y > 0&& (!findfunc(map[elem->pos.y-1][elem->pos.x], STOP)))
			{
				if (time % 5 == 0)
				{
					map[elem->pos.y][elem->pos.x] = null_elem;
					elem->pos.y--;
				}
			}
			else
				remove(elem->pos, elements, P_BULLET);
		}
		if (findfunc(elem->prop, MOVE))
		{
			if (findfunc(map[elem->pos.y][elem->pos.x + change_x], STOP))
			{
				change_x = -change_x;
			}
			else
			{
				;
			}
			if (time % 60 == 0)
			{
				elem->pos.x += change_x;
			}
			if (time % 600 == 0)
			{
				elem->pos.y += change_y;
				time = 0;
			}
		}
	}
	time++;
	if (insert != STAY)
	{
		InputInfo lhs;
		for (size_t i = 0; i < MAP_Y; i++)
		{
			for (size_t j = 0; j < MAP_X; j++)
			{
				lhs.map[i][j] = map[i][j];
			}
		}
		
		for (auto a : elements)
		{
			auto lhs_elem = createBox(a->prop.first);
			lhs_elem->pos.y = a->pos.y;
			lhs_elem->pos.x = a->pos.x;
			lhs.elements.push_back(lhs_elem);
		}
		inputList.push_back(lhs);
	}
}

int stage::stageInput()
{
	if (GetKeyboardTrigger(DIK_W))
	{
		return UP;
	}
	else if (GetKeyboardTrigger(DIK_S))
	{
		return DOWN;
	}
	else if (GetKeyboardTrigger(DIK_A))
	{
		return LEFT;
	}
	else if (GetKeyboardTrigger(DIK_D))
	{
		return RIGHT;
	}
	else if (GetKeyboardTrigger(DIK_J))
	{
		return BULLET;
	}
	else if (GetKeyboardTrigger(DIK_TAB))
	{
		memoryReset();
		if (++current_map < MAPEND)
			;
		else
			current_map = MAP1;
		mapInit();
	}
	else if (GetKeyboardTrigger(DIK_R))
	{
		memoryReset();
		mapInit();
	}
	else if (GetKeyboardTrigger(DIK_SPACE))
	{
		if (inputList.size()-1)
		{
			inputList.pop_back();
			auto lhs = inputList.end() - 1;
			for (size_t i = 0; i < MAP_Y; i++)
			{
				for (size_t j = 0; j < MAP_X; j++)
				{
					map[i][j] = lhs->map[i][j];
				}
			}
			std::vector<Box*>().swap(elements);
			for (auto a : lhs->elements)
			{
				elements.push_back(a);
			}
		}
		return STAY;
	}
	else
		return STAY;

}

void stage::stageDraw(LPDIRECT3DDEVICE9 dev)
{
	//background draw
	DrawQuad(0, 0, 800, 800, dev, tex_background[current_map]);

	//box draw
	for (auto elem : elements)
	{
		auto i = elem->prop.first;

		if ((!elem->prop.second.size()))
		{
			if (i < 256 && i >= 0)
			{
				DrawQuad(elem->pos.x, elem->pos.y, dev, tex_left[i]);
			}
			else if (i < 512 && i >= 256)
			{
				DrawQuad(elem->pos.x, elem->pos.y, dev, tex_picture[i - 256]);
			}
			else if (i < 768 && i >= 512)
			{
				DrawQuad(elem->pos.x, elem->pos.y, dev, tex_right[i - 512]);
			}
			else if (i < 1024 && i >= 768)
			{
				DrawQuad(elem->pos.x, elem->pos.y, dev, tex_def[i - 768]);
			}
		}
	}
	for (auto elem : elements)
	{
		static bool step = false;
		static unsigned time = 0;
		time++;
		auto i = elem->prop.first;
		if (elem->prop.second.size())
		{
			if (time > 4000)
			{
				time = 0;
				step = !step;
			}
			if (i == P_SUNNY&&findfunc(elem->prop, YOU))
			{
				if (step)
					DrawQuad(elem->pos.x, elem->pos.y, dev, tex_amelie[0]);
				else
					DrawQuad(elem->pos.x, elem->pos.y, dev, tex_amelie[1]);
			}
			else if (i == P_WATER&&findfunc(elem->prop, SINK))
			{
				if (step)
					DrawQuad(elem->pos.x, elem->pos.y, dev, tex_amelie[2]);
				else
					DrawQuad(elem->pos.x, elem->pos.y, dev, tex_amelie[3]);
			}
			else if (i == P_HAT)
			{
				if (step)
					DrawQuad(elem->pos.x, elem->pos.y, dev, tex_amelie[4]);
				else
					DrawQuad(elem->pos.x, elem->pos.y, dev, tex_amelie[5]);
			}
			else if (i < 256 && i >= 0)
			{
				DrawQuad(elem->pos.x, elem->pos.y, dev, tex_left[i]);
			}
			else if (i < 512 && i >= 256)
			{
				DrawQuad(elem->pos.x, elem->pos.y, dev, tex_picture[i - 256]);
			}
			else if (i < 768 && i >= 512)
			{
				DrawQuad(elem->pos.x, elem->pos.y, dev, tex_right[i - 512]);
			}
			else if (i < 1024 && i >= 768)
			{
				DrawQuad(elem->pos.x, elem->pos.y, dev, tex_def[i - 768]);
			}
		}
	}
}

//not member function
Box* createBox(unsigned i)
{
	if (i < 256 && i >= 0)
	{
		return new Left_N(i);
	}
	else if (i < 512 && i >= 256)
	{
		return new Pic(i);
	}
	else if (i < 768 && i >= 512)
	{
		return new Right_Adj(i);
	}
	else if (i < 1024 && i >= 768)
	{
		return new Def(i);
	}
	else
		return nullptr;
}

bool norepeat(FuncId& b, BoxId& a)
{
	for (auto c : b)
	{
		if (c == a)
			return false;
	}
	return true;
}

void remove(Pos& lhs, std::vector<Box*>&elements,const int& i)
{
	if (i == SINK)
	{
		for (auto elem = elements.begin(); elem != elements.end(); elem++)
		{
			if ((*elem)->pos.x == lhs.x && (*elem)->pos.y == lhs.y)
			{
				map[lhs.y][lhs.x] = null_elem;
				elem = elements.erase(elem) - 1;
			}
		}
	}
	else if (i == KILL)
	{
		for (auto elem = elements.begin(); elem != elements.end(); elem++)
		{
			if ((*elem)->pos.x == lhs.x && (*elem)->pos.y == lhs.y&&(!findfunc((*elem)->prop,KILL)))
			{
				map[lhs.y][lhs.x] = null_elem;
				elem = elements.erase(elem) - 1;
			}
		}
	}
	else if (i == P_BULLET)
	{
		for (auto elem = elements.begin(); elem != elements.end(); elem++)
		{
			if ((*elem)->pos.x == lhs.x && (*elem)->pos.y == lhs.y && (*elem)->prop.first==P_BULLET)
			{
				map[lhs.y][lhs.x] = null_elem;
				elem = elements.erase(elem) - 1;
			}
		}
	}
}

void stage::setNextstage(const bool& i)
{
	next_stage = i;
}
