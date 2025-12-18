#pragma once
#include "tile.h"
#include <random>

Tile::Tile()
{
	//画像データをロードする
	turf_img = LoadGraph("image\\turf.png");
	tile_img[TILES::EMPTY] = LoadGraph("image\\empty.png");
	tile_img[TILES::ONE] = LoadGraph("image\\one.png");
	tile_img[TILES::TWO] = LoadGraph("image\\two.png");
	tile_img[TILES::THREE] = LoadGraph("image\\three.png");
	tile_img[TILES::FOUR] = LoadGraph("image\\four.png");
	tile_img[TILES::FIVE] = LoadGraph("image\\five.png");
	tile_img[TILES::SIX] = LoadGraph("image\\six.png");
	tile_img[TILES::SEVEN] = LoadGraph("image\\seven.png");
	tile_img[TILES::FRAG] = LoadGraph("image\\frag.png");
	tile_img[TILES::MINE] = LoadGraph("image\\mine.png");

	//タイルの初期化
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		map[i].num = 0;
		map[i].open = false;
		map[i].flag = false;
		map[i].pos = { (i % MAP_WIDTH) * TILE_WIDTH,(i / MAP_WIDTH) * TILE_HEIGHT + TILE_HEIGHT * 3 / 2 };
	}
}

void Tile::Action()
{
	//マウスカーソルの位置を取得
	GetMousePoint(&mouse.x, &mouse.y);

	//タイル除去
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !clickflag[CLICKFLAG::LEFT])
	{
		CheckClick(CLICKFLAG::LEFT);
	}
	clickflag[CLICKFLAG::LEFT] = (GetMouseInput() & MOUSE_INPUT_LEFT);

	//フラグ設置
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && !clickflag[CLICKFLAG::RIGHT])
	{
		CheckClick(CLICKFLAG::RIGHT);
	}
	clickflag[CLICKFLAG::RIGHT] = (GetMouseInput() & MOUSE_INPUT_RIGHT);

	//リセット
	if (CheckHitKey(KEY_INPUT_R))
	{
		ResetTile();
	}
	resetflag = CheckHitKey(KEY_INPUT_R);
}

void Tile::ResetTile()
{
	//タイルの初期化
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		map[i].num = 0;
		map[i].open = false;
		map[i].flag = false;
		map[i].pos = { (i % MAP_WIDTH) * TILE_WIDTH,(i / MAP_WIDTH) * TILE_HEIGHT + TILE_HEIGHT * 3 / 2 };
	}

	setmineflag = false;
}

void Tile::CheckClick(int _LR)
{
	//どのタイルがクリックされたか調べる
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		Point checker{ (i % MAP_WIDTH) * TILE_WIDTH ,(i / MAP_WIDTH) * TILE_HEIGHT + TILE_HEIGHT * 3 / 2 };
		if (checker.x < mouse.x && mouse.x < checker.x + TILE_WIDTH && checker.y < mouse.y && mouse.y < checker.y + TILE_HEIGHT)
		{
			if (!map[i].open)
			{
				if (_LR == CLICKFLAG::LEFT && !map[i].flag)
				{
					if (!setmineflag)
					{
						SetMine(i);
						setmineflag = true;
					}
					map[i].open = true;
					OpenChainTiles(i);
				}
				else if (_LR == CLICKFLAG::RIGHT)
				{
					if (map[i].flag)
					{
						map[i].flag = false;
					}
					else
					{
						map[i].flag = true;
					}
				}
			}
		}
	}
}

void Tile::SetMine(int _tn)
{
	int point;
	//爆弾を３０個生成する
	for (int i = 0; i < BOMB_NUM; i++)
	{
		while (1) {
			point = GetRandNum(0, MAP_WIDTH * MAP_HEIGHT);
			if (map[point].num != TILES::MINE && CheckClickBox(_tn, point))
			{
				break;
			}
		}
		map[point].num = TILES::MINE;

		if (point % MAP_WIDTH != 0)
		{
			AddTileNum(point, CHECKTILE::DOWNLEFT);
			AddTileNum(point, CHECKTILE::MIDDLELEFT);
			AddTileNum(point, CHECKTILE::UPLEFT);
		}
		if (point % MAP_WIDTH != MAP_WIDTH - 1)
		{
			AddTileNum(point, CHECKTILE::DOWNRIGHT);
			AddTileNum(point, CHECKTILE::MIDDLERIGHT);
			AddTileNum(point, CHECKTILE::UPRIGHT);
		}
		AddTileNum(point, CHECKTILE::DOWNMIDDLE);
		AddTileNum(point, CHECKTILE::UPMIDDLE);
	}
}

int Tile::GetRandNum(int min, int max)
{
	int num;
	while (1) {
		num = GetRand(max + SUB_RANDMAXNUM);
		if (num > min)
		{
			return num;
		}
	}
}

void Tile::AddTileNum(int _p,int _dir)
{
	if (_p + _dir >= 0 && _p + _dir < MAP_WIDTH * MAP_HEIGHT)
	{
		//爆弾じゃないところの数字を増やす
		if (map[_p + _dir].num != TILES::MINE)
		{
			map[_p + _dir].num++;
		}
	}
}

bool Tile::CheckClickBox(int _tn, int _p)
{
	if (_p != _tn + CHECKTILE::DOWNLEFT && _p != _tn + CHECKTILE::DOWNMIDDLE && _p != _tn + CHECKTILE::DOWNRIGHT && _p != _tn + CHECKTILE::MIDDLELEFT && _p != _tn && _p != _tn + CHECKTILE::MIDDLERIGHT && _p != _tn + CHECKTILE::UPLEFT && _p != _tn + CHECKTILE::UPMIDDLE && _p != _tn + CHECKTILE::UPRIGHT)
	{
		return true;
	}

	return false;
}

void Tile::OpenChainTiles(int _tn)
{
	if (map[_tn].num == TILES::EMPTY)
	{
		//八方向のタイルを開いていく
		if (_tn % MAP_WIDTH != 0)
		{
			if (_tn + CHECKTILE::UPLEFT >= 0)
			{
				OpenTile(_tn, CHECKTILE::UPLEFT);
			}
			if (_tn + CHECKTILE::MIDDLELEFT >= 0)
			{
				OpenTile(_tn, CHECKTILE::MIDDLELEFT);
			}
			OpenTile(_tn, CHECKTILE::DOWNLEFT);
		}
		if (_tn % MAP_WIDTH != MAP_WIDTH - 1)
		{
			if (_tn + CHECKTILE::UPRIGHT)
			{
				OpenTile(_tn, CHECKTILE::UPRIGHT);
			}
			OpenTile(_tn, CHECKTILE::MIDDLERIGHT);
			OpenTile(_tn, CHECKTILE::DOWNRIGHT);
		}
		if (_tn + CHECKTILE::UPMIDDLE)
		{
			OpenTile(_tn, CHECKTILE::UPMIDDLE);
		}
		OpenTile(_tn, CHECKTILE::DOWNMIDDLE);
	}
}

void Tile::OpenTile(int _tn, int _rad)
{
	if (!map[_tn + _rad].open)
	{
		map[_tn + _rad].open = true;
		OpenChainTiles(_tn + _rad);
	}
}

//タイルを表示する関数
void Tile::DrawTile()
{
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		if (!map[i].open)
		{
			DrawGraph(map[i].pos.x, map[i].pos.y, turf_img, true);
			if (map[i].flag)
			{
				DrawGraph(map[i].pos.x, map[i].pos.y, tile_img[FRAG], true);
			}
		}
		else
		{
			DrawGraph(map[i].pos.x, map[i].pos.y, tile_img[map[i].num], true);
		}

	}
}

Tile::~Tile()
{

}